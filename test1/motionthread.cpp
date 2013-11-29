#include "motionthread.h"

#include <QDir>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>

#include "utils/iocompression.h"

MotionThread::MotionThread(QObject *parent) :
    QThread(parent), m_continue(true)
{
}

MotionThread::MotionThread(const QString& filename, QObject *parent) :
    QThread(parent), m_filename(filename), m_continue(true)
{
}

void MotionThread::setSteps(Steps steps)
{
    m_steps = steps;
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

    while (textStream.atEnd() == false) {
        foreach (QString number, textStream.readLine().split(",")) {
            float num = number.trimmed().toFloat();
            num = num < 0 ? -num : num;
            //exclude too small values
            if (num < _minThreshold) { continue; }
            m[num] += 1;
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
    QString resultDir = "motionData";
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
            emit logText("Processing with" + QString::number(threadCount) + " thread(s)");
            dir.mkdir("clusters");
            QString clusterPath = resultDir + "/clusters";
            QFileInfoList files = dir.entryInfoList(QDir::Files, QDir::Name);
            for (int fpos = 0; fpos < files.size(); ++fpos){
                QFileInfo file = files.at(fpos);
                if (file.suffix().compare("gz") != 0) { continue; }
                emit logText("<font color=\"blue\">("
                        + QString::number((int)((float)fpos / (float)files.size() * 100.f))
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
                    QList<QByteArray> mapInput;
                    for (int i = dataBegin + cut; i < length; i++) {
                        if (content.at(i) == sep) {
                            mapInput.append(content.mid(last + 1, i - last - 1));
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

                    //IMPORTANT : do not work in debug mode with MSVC (error in msvcrt100)
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

                    //merge clusters
                    QList<cluster> result;
                    foreach (QList<cluster>* clustList, results) {
                        for (int i = 0; i < clustList->size(); ++i) {
                            if (i == 0 && result.size() != 0) {
                                cluster c1 = result.last();
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



                    //3.saving clusters

                    QFile out(QString("%1/%2.clust").arg(clusterPath).arg(file.fileName()));
                    out.open(QFile::WriteOnly);
                    foreach (cluster c, result) {
                        out.write(QString(QString::number(c.avg) + "\n").toLocal8Bit().constData());
                    }
                    out.close();
            }


        }
    } else {
        emit logText("Skipped.");
    }

    emit logText("Ended", "green", false, true);
}
