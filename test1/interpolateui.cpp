#include "interpolateui.h"
#include "ui_interpolateui.h"

#include <QDir>

#include "utils/filesutils.h"

#include <QDebug>

InterpolateUi::InterpolateUi(SplineDrawer* spline, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterpolateUi)
    , m_sequences(QList<Sequence*>())
    , m_spline(spline)
    , m_optflowtools(OpticalFlowTools()) {
    ui->setupUi(this);
}

InterpolateUi::~InterpolateUi() {
    delete ui;
}

void InterpolateUi::addBaseName(const QString &basename)
{
    ui->txtSrc->setText(basename + "_Frames/");
    ui->txtOut->setText(basename + "_InterpFrames/");
}

void InterpolateUi::setTpf(const QString &tpf)
{
    if (tpf.isEmpty()) { return; }
    ui->txtRate->setText(tpf);
}

void InterpolateUi::on_btInterpolate_clicked() {
    ui->btInterpolate->setEnabled(false);

    //load sequences profile
    m_sequences.clear();

    //direct
    emit needSequences(m_sequences);

    //check dirs
    QString strOutdir = ui->txtOut->text();
    if (strOutdir.isEmpty()) {
        return;
    }
    QString strSrcdir = ui->txtSrc->text();
    if (strSrcdir.isEmpty()) {
        return;
    }
    unsigned float tpf = 0;
    try {
        tpf = ui->txtRate->text().toFloat();
    } catch (...) {
        return;
    }


    QDir srcdir(strSrcdir);
    QStringList filterFlow;
    filterFlow << "*.gz";
    QFileInfoList images = srcdir.entryInfoList(getSupportedImagesFilter()
                           , QDir::Files
                           , QDir::Name);
    QFileInfoList flows = srcdir.entryInfoList(filterFlow
                          , QDir::Files
                          , QDir::Name);

    QDir destdir("./");
    destdir.mkdir(strOutdir);
    destdir.cd(strOutdir);
    if (!(strOutdir.endsWith("/") || strOutdir.endsWith("\\"))) {
        strOutdir += "/";
    }

    sortFiles(images);
    sortFiles(flows);

    ulong currentTime = 0;

    float accf(0.f);

    /*** log  **/
    bool log = ui->chkLog->isChecked();
    QTextStream* out(NULL);
    QFile* file;

    if (log) {
        file = new QFile("log_interpolate.txt");
        file->open(QIODevice::Append | QIODevice::Text);
        out = new QTextStream(file);
    }
    /************/

    int outnumber(0);
    for (int i = 0; i < images.size() - 1; ++i) {
        //extract frame number from filename
        const QFileInfo qfile1 = images.at(i);
        const QFileInfo qfile2 = images.at(i + 1);
        int frameNumber;
        sscanf(qfile1.baseName().toLocal8Bit().constData(), "img%d", &frameNumber);

        //interpolate
        QImage frame1(qfile1.absoluteFilePath());
        QImage frame2(qfile2.absoluteFilePath());
        //QString interpName(strOutdir + "img" + QString::number(frameNumber) + "_");
        ++outnumber;
        QString ext = "." + qfile1.completeSuffix();
        QString outnumberString((outnumber < 10 ? "000" : outnumber < 100 ? "00" : outnumber < 1000 ? "0" : "") + QString::number(outnumber));
        QString interpName(strOutdir + "img" + outnumberString + ext);
        int count(0);

        //interpolate residual accumaltor
        if (accf > 1 || accf < 0) {
            if (log) { *out << "fatal error : residual accf > 1 or < 0 (" << accf << ") !\n"; }
            qDebug() << "fatal error : residual accf > 1 or < 0 (" << accf << ") !";
            break;
        } else if (accf != 0 && accf < 1) {
            //directly interpolate and reset accf
            //QString interpNameFull = interpName + QString::number(count) + ext;
            QString interpNameFull(interpName);
            QImage* interpolatedFrame;
            interpolatedFrame = m_optflowtools.interpolate(&frame1, &frame2
                                                           , accf
                                                           , qfile1.absoluteFilePath()
                                                           , qfile2.absoluteFilePath()
                                                           , strOutdir
                                                           , "_" + QString::number(count));
            if (interpolatedFrame != NULL) { //library was used instead of exe
                interpolatedFrame->save(interpNameFull);
                delete interpolatedFrame;
            }
            if (log) { *out << "interpolation : residual accf : " << accf
                            << " -> " << interpNameFull << "\n"; }
            ++count;

        } else if (accf == 1){
            //QString interpNameFull = interpName + QString::number(count) + ext;
            QString interpNameFull(interpName);
            frame1.save(interpNameFull);
            if (log) {*out << "residual acc -> frame1 saved : " << interpNameFull << "\n"; }
            ++count;
        }

        //get interpolation factor
        QList<float> ratios;
        ratios = m_spline->getInterpolationFactors(tpf, tpf * i + tpf * accf);

        accf = 0;

        if (log) {*out << "***image number " << i << " (ratios size : " << ratios.size() << ")" << "\n"; }
        if (log) {*out << "interpname " << interpName << " Loop through ratios : \n"; }

        foreach (float f, ratios) {

            //update currentTime
            currentTime += tpf * f;
            accf += f;

            if (log) {*out << "cur f : " << f << " , currentTime : "
            << currentTime << " , accf : " << accf << " , count : " << count; }

            if (accf > 1) {
                //we have either an acceleration, or we need to interpolate
                //part of the next frame
                int offset(-1);
                do {
                    accf -= 1.f;
                    ++offset; //jump to next frames
                } while (accf > 1);
                i += offset;

                if (log) {*out << "\naccf > 1, offset : " << offset
                << " , i : " << i << " , currentTime changed to " << currentTime << "\n"; }

                break;
            }

            QString outnumberString((outnumber < 10 ? "000" : outnumber < 100 ? "00" : outnumber < 1000 ? "0" : "") + QString::number(outnumber));
            QString interpName(strOutdir + "img" + outnumberString + ext);
            //QString interpNameFull = interpName + QString::number(count) + ext;
            QString interpNameFull(interpName);
            if (accf == 0) {
                frame1.save(interpNameFull);
                if (log) {*out << " -> frame1 saved : " << interpNameFull << "\n"; }
            } else if (accf == 1) {
                frame2.save(interpNameFull);
                if (log) {*out << " -> frame2 saved : " << interpNameFull << "\n"; }
                accf = 0;
            } else {
                QImage* interpolatedFrame;
                interpolatedFrame = m_optflowtools.interpolate(&frame1, &frame2
                                                               , accf
                                                               , qfile1.absoluteFilePath()
                                                               , qfile2.absoluteFilePath()
                                                               , strOutdir
                                                               , "_" + QString::number(count));
                if (interpolatedFrame != NULL) { //library was used instead of exe
                    interpolatedFrame->save(interpNameFull);
                    delete interpolatedFrame;
                }

                if (log) {*out << " -> frame_interp saved : " << interpNameFull << "\n"; }
            }

            ++count;
            ++outnumber;

            QCoreApplication::processEvents();
        }

        //update progress bar
        ui->pbProgress->setValue(ceil((float)((float)(i+1) / (float)images.size() * 100.f)));
        ui->pbProgress->update();

         if (log) { out->flush(); }
       }

    ui->btInterpolate->setEnabled(true);

    if (log) {*out << "---end--- " << "\n"; }
    if (log) {    out->flush(); file->close(); delete out; delete file; }

    ui->pbProgress->setValue(100);
}

void InterpolateUi::closeEvent(QCloseEvent*) {
    emit windowClosed("interpolation");
}
