#include "motionthread.h"

#include <QDir>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>

#include "utils/iocompression.h"
#include "utils/filesutils.h"
#include "mathlib/filtering.h"

MotionThread::MotionThread(QObject *parent) :
    QThread(parent), m_continue(true), m_smoothingIntensity(_windowSizeFirstPass)
{
}

MotionThread::MotionThread(const QString& filename, QObject *parent) :
    QThread(parent), m_filename(filename), m_continue(true), m_smoothingIntensity(_windowSizeFirstPass)
{
}

void MotionThread::setSteps(Steps steps)
{
    m_steps = steps;
}

void MotionThread::setOthers(OtherFlags flags)
{
    m_others = flags;
}

void MotionThread::addFilesFilters(QString filter)
{
    if (filter.isEmpty()) { return; }
    m_filesFilters << filter;
}

void MotionThread::setSmootingIntensity(int smoothing)
{
    if (smoothing >= 0) {
        m_smoothingIntensity = smoothing;
    }
}

void MotionThread::close()
{
    m_continue = false;
}

//Mapreduce stuff -------------------------------------------
MotionThread::motions parse(const QByteArray& piece)
{
    QTextStream textStream(piece, QIODevice::ReadOnly);
    MotionThread::motions m;

    /*
     * format of the file :
     * dx, dy, dx, dy, ...
     */
    bool pairFound = false;
    float dx, dy;

    while (textStream.atEnd() == false) {

        foreach (QString number, textStream.readLine().split(",")) {
            QString trim = number.trimmed();
            if (trim.isEmpty()) { continue; }
            float num = trim.toFloat();

            if (!pairFound) {
                dx = num;
            } else {
                dy = num;
                float sqrtnorm = dx*dx + dy*dy;
                //exclude too small values
                if (sqrtnorm >= _minThreshold) {
                    m[sqrtnorm] += 1;
                }
            }
            pairFound = !pairFound;
        }
    }

    return m;
}
void reduce(MotionThread::motions &result, const MotionThread::motions &w)
{
    QMapIterator<float, int> i(w);
    while (i.hasNext()) {
        i.next();
        result[i.key()] += i.value();
    }
}

//-----------------------------------------------------------

void MotionThread::run()
{
    if (m_filename.isEmpty()) { emit logText("Filename not correct.", "red"); return; }
    QString cmd = "wflow.exe";
    QFileInfo fileinfo = QFileInfo(m_filename);
    if (!fileinfo.exists()) { emit logText("Input file does not exist.", "red"); return; }
    QString resultDir = fileinfo.baseName() + "motionData";
    QString clusterPath = resultDir + "/clusters";
    QProcess process;
    QStringList args;

    emit logText("Computing motion data... (1/3)", "orange");

    if (m_continue && ((m_steps & Affine) == Affine)) {
        args << m_filename << resultDir << "-M" << "1";
        emit logText("<i>./wflow</i> " + m_filename + " ./" + resultDir + " -M 1");

        int res;
        res = process.execute(cmd, args);
        switch (res) {
        case -2:
            emit logText("Process cannot be started.", "red");
            break;
        case -1:
            emit logText("Process crashed.", "red");
            break;
        default:
            emit logText("Process returned : <font color=\"blue\">" + QString::number(res) + "</font>");
        }

        process.waitForFinished();
        process.close();

    } else {
        emit logText("Skipped.");
    }

    emit logText("Computing omega flow... (2/3)", "orange");

    if (m_continue && ((m_steps & wflow) == wflow)) {
        args.clear();
        args << m_filename << resultDir << "-T" << "1" << "-C" << "0";
        emit logText("<i>./wflow</i> " + m_filename + " ./" + resultDir + " -T 1 -C 0");

        bool useGZip = false;
        QProcess gzip;
        if (useGZip) {
            //simulate : .. | gzip > flow.features.gz
            gzip.setStandardOutputFile("flow.features.gz");
            gzip.setStandardInputFile("flow.features");
            process.setStandardOutputProcess(&gzip);
        }

        int res;
        res = process.execute(cmd, args);
        //res = process.execute("wflow.exe " + filename + " motionData -T 1 -C 0 | gzip > features.gz");
        switch (res) {
        case -2:
            emit logText("Process cannot be started.", "red");
            break;
        case -1:
            emit logText("Process crashed.", "red");
            break;
        default:
            emit logText("Process returned : <font color=\"blue\">" + QString::number(res) + "</font>");
        }

        process.waitForFinished();

        if (useGZip) {
            gzip.execute("gzip");
            gzip.waitForFinished();
        }

    } else {
        emit logText("Skipped.");
    }

    emit logText("profiling... (3/3)", "orange");

    int count = 0;
    if (m_continue && ((m_steps & Profile) == Profile)) {
        QDir dir(resultDir);
        if (!dir.exists()) {
            emit logText("Error opening " + resultDir, "red", true);
        } else {

            /* gzip -d all files and compute clusters
             * using mapreduce
             */
            int threadCount = QThread::idealThreadCount();
            if (threadCount == 0) { threadCount = 1; }
            emit logText("Processing with " + QString::number(threadCount) + " thread(s)");
            dir.mkdir("clusters");
            QFileInfoList files = dir.entryInfoList(QDir::Files, QDir::Name);

            //filter and order the files (the default Name ordering is wrong)
            QFileInfoList flowFiles;
            flowFiles.reserve(files.size());
            for (int fpos = 0; fpos < files.size(); ++fpos){
                QFileInfo file = files.at(fpos);
                if (file.suffix().compare("gz") != 0) { continue; }
                bool found = false;
                foreach (QString filter, m_filesFilters) {
                    if (file.baseName().contains(filter)) {
                        found = true; break;
                    }
                }

                if (found) { flowFiles.append(file); }
            }

            sortFiles(flowFiles);

            //curve container
            std::vector<float> values;
            values.reserve(files.size());

            //go through all files that contains the w-flow
            for (int fpos = 0; fpos < flowFiles.size(); ++fpos){
                QFileInfo file = flowFiles.at(fpos);
//                if (file.suffix().compare("gz") != 0) { continue; }
                emit logText("<font color=\"blue\">("
                        + QString::number((int)ceil((((float)fpos+1.f) / (float)flowFiles.size() * 100.f)))
                        + "%)</font> Processing file : <i>" + file.fileName() + "</i>");
                    QByteArray content = gzipUncompress(file.absoluteFilePath());

                    //1.start mapreduce for ordering
                    /*
                     * 1.1 parse the file, prepare input for mappers
                     */
                    int length = content.size();
                    if (length == 0) { continue; }

                    int dataBegin = content.indexOf("[ ") + 1;

                    int cut = (length - dataBegin) / threadCount;
                    if (cut == 0) { cut = (length - dataBegin) / (threadCount / 2.f); }
                    if (cut == 0) { cut = 1; }

                    char sep = ',';
                    int last = dataBegin;
                    bool adjust = false;
                    QList<QByteArray> mapInput;
                    for (int i = dataBegin + cut; i < length; i++) {
                        if (content.at(i) == sep) {
                            QByteArray ar = content.mid(last + 1, i - last - 1);
                            //fix : ensure we are not cutting a pair
                            if (!adjust && ar.count(sep) % 2 == 0) {
                                adjust = true;
                                continue;
                            }

                            adjust = false;
                            mapInput.append(ar);
                            last = i + 1;
                            i += cut;
                            if (i >= length) { // we are cutting a too big piece, this is the last one
                                mapInput.append(content.mid(last, length - last - 3)); //without " ]"
                            }
                        }
                    }

                    /*
                     * 1.2 do mr, and wait it finishes
                     */

                    //IMPORTANT : does not work in debug mode with MSVC (error in msvcrt100)
                    motions motionResults = QtConcurrent::mappedReduced(mapInput, parse, reduce);                    

                    //2.clusterizing

                    /*
                     * 2.1 linearly go through the list and find clusters
                     */

                    QList<float> keys = motionResults.keys();
                    QList<QList<cluster>*> results;
                    QList<Clusterizer*> clusterizers;
                    QList<QFuture<void>> futures;
                    results.reserve(threadCount);
                    clusterizers.reserve(threadCount);

                    int range = keys.size() / threadCount;

                    for (int i = 0; i < threadCount; i++) {
                        results.append(new QList<cluster>());
                        Clusterizer* clusterizer = new Clusterizer(keys, results.at(i)
                                                 , i * range
                                                 , (i != threadCount - 1) ? i * range + range : keys.size());
                        futures.append(QtConcurrent::run(clusterizer, &Clusterizer::clusterize));
                    }

                    foreach (QFuture<void> future, futures) {
                        future.waitForFinished();
                    }

//                    QFile out2(QString("testCluster%1.txt").arg(file.fileName()));
//                    out2.open(QFile::WriteOnly);
//                    QList<float> keystest = motionResults.keys();
//                    foreach (float f, keystest) {
//                        out2.write(QString(QString::number(f) + "\n").toLocal8Bit().constData());
//                    }
//                    out2.close();

                    //merge clusters
                    QList<cluster> result;
                    foreach (QList<cluster>* clustList, results) {
                        for (int i = 0; i < clustList->size(); ++i) {
                            if (i == 0 && result.size() != 0) {
                                cluster c1 = result.last(); result.removeLast(); //pop
                                cluster c2 = clustList->at(i);
                                if (c2.start - c1.end < _maxDistInsideCluster) {
                                    cluster c12;
                                    c12.start = c1.start;
                                    c12.end = c2.end;
                                    c12.size = c1.size + c2.size;
                                    c12.avg = (c1.avg * c1.size + c2.avg * c2.size) / c12.size;
                                    result.append(c12);
                                }
                            } else {
                                result.append(clustList->at(i));
                            }
                        }
                    }

                    //release rsrces
                    foreach (Clusterizer* cer, clusterizers) {
                        delete cer;
                    }
                    foreach (QList<cluster>* clustList, results) {
                        delete clustList;
                    }

                    /*
                     * 2.2 prune the extra clusters regarding its neighbors frames
                     */

                    //Done with spline fitter

                    //3.saving clusters

                    //compute object motion avg

                    float sum(0.f);
                    int size(0);
                    foreach (cluster c, result) {
                        sum += c.avg;
                        ++size;
                    }

//                    if ((m_others & WriteMotion) == WriteMotion) {
//                        QFile out(QString("%1/%2.clust").arg(clusterPath).arg(file.fileName()));
//                        out.open(QFile::WriteOnly);
//                        out.write(QString(QString::number(sum / size) + "\n").toLocal8Bit().constData());
//                        out.close();
//                    }

                    values.push_back(sum / size);

                    //debug
//                    count++;
//                    if (count == 30) { break; }
            }

            //we have the values, apply filters

            emit logText("finalizing...");
            std::vector<float> filtered2;
            if (m_smoothingIntensity != 0) {
                std::vector<float> filtered;
                filtered.reserve(values.size());
                filtered2.reserve(values.size());
                filter::movingAverage(values, filtered, m_smoothingIntensity);
                filter::movingAverage(filtered, filtered2, m_smoothingIntensity - 1);
            } else {
                filtered2 = values;
            }

            //save filtered values
            if ((m_others & WriteMotion) == WriteMotion) {
                QFile out(QString("%1/motion.clust").arg(clusterPath));
                out.open(QFile::WriteOnly);
                foreach (float f, filtered2) {
                    out.write(QString(QString::number(f) + "\n").toLocal8Bit().constData());
                }
                out.close();
            }

            emit motionProfileComputed(m_filename, filtered2);

        }
    } else {
        emit logText("Skipped.");
    }

    if (m_continue && (m_steps == None)) {
        emit logText("Searching for existing data...");

        QFile filec(clusterPath + "/motion.clust");
        if (!filec.open(QFile::ReadOnly)) {
            emit logText("Could not find motion.clust under " + clusterPath, "red");
        } else {
            QByteArray buff = filec.readLine();
            std::vector<float> profile;

            while (!buff.isEmpty()) {
                profile.push_back(QString(buff).toFloat());
                buff = filec.readLine();
            }

            filec.close();

            emit motionProfileComputed(m_filename, profile);
            emit logText("Motion profile loaded into main window.");
        }

    }

    emit logText("Ended", "green", false, true);
}
