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
    int tps = 0;
    try {
        tps = ui->txtRate->text().toInt();
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

    for (int i = 0; i < images.size() - 1; ++i) {
        //extract frame number from filename
        const QFileInfo qfile1 = images.at(i);
        const QFileInfo qfile2 = images.at(i + 1);
//        const QFileInfo flow12 = flows.at(i);
        int frameNumber;
        sscanf(qfile1.baseName().toLocal8Bit().constData(), "img%d", &frameNumber);

        //get interpolation factor

        QList<float> ratios;
        ratios.append(accf);
        ratios = m_spline->getInterpolationFactors(tps, currentTime);

        //interpolate
        QImage frame1(qfile1.absoluteFilePath());
        QImage frame2(qfile2.absoluteFilePath());
        QString interpName(strOutdir + "img" + QString::number(frameNumber) + "_");
        QString ext = qfile1.completeSuffix();
        int count(0);

        QString dbg("ratios");
        int offset(-1);
        foreach (float f, ratios) {
            dbg += " : " + QString::number(accf);

            if (accf > 1) {
                //we have either an acceleration, or we need to interpolate
                //part of the next frame
                do {
                    accf -= 1.f;
                    ++offset; //jump to next frames
                } while (accf > 1);
                i += offset;
                currentTime += tps * accf;
                break;
            }

            if (accf == 0) {
                frame1.save(interpName + count + ext);
            } else if (accf == 1) {
                frame2.save(interpName + count + ext);
            } else {
                QImage* interpolatedFrame;
                interpolatedFrame = m_optflowtools.interpolate(&frame1, &frame2
                                                               , accf
                                                               , qfile1.absoluteFilePath()
                                                               , qfile2.absoluteFilePath()
                                                               , strOutdir
                                                               , "_" + QString::number(count));
                if (interpolatedFrame != NULL) { //library was used instead of exe
                    interpolatedFrame->save(interpName + count + ext);
                    delete interpolatedFrame;
                }
            }

            accf += f;

            ++count;
            currentTime += tps * f;
        }

        //ratio stands below 1
        if (offset == -1) {
            accf = 0; //then reset accumulator
        }

        //update progress bar
        ui->pbProgress->setValue(ceil((float)((i+1) / images.size() * 100)));
        ui->pbProgress->update();
       }

    ui->btInterpolate->setEnabled(true);
}

void InterpolateUi::closeEvent(QCloseEvent*) {
    emit windowClosed("interpolation");
}
