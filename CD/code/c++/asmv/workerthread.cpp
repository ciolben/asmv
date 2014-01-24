#include "workerthread.h"

#include <QTime>
#include <QStringBuilder>
#include <QDir>
#include <QDebug>

WorkerThread::WorkerThread(QObject *parent, QLabel *renderTarget, VideoTools* vTools, ImageEaterThread& _imageEater)
    : QThread(parent)
    , renderTarget(renderTarget)
    , vtools(vTools)
    , bwFrames(0)
    , duration(0)
    , filename("out/")
    , imageEater(_imageEater)
{

}

void WorkerThread::close() {
    duration = 0;
}

void WorkerThread::run() {
    QImage* img;
    QString ext = ".jpg";

    int curCounter = 0;
    int frameToSkip = vtools->getFramesToSkip();

    //*****setup imageEater
    imageEater.setBufferSize(3);
    //imageEater.setRate(1000);
    imageEater.start();
    //*****

    //check if filename ends with /
    if (!(filename.endsWith("/") || filename.endsWith("\\"))) {
        filename += "/";
    }
    QDir outdir(filename);
    if (!outdir.exists()) {
        if (outdir.isRelative()) {
            QDir root(".");
            root.mkpath(filename);
        } else {
            QDir root(filename.mid(0, 3) + "/");
            root.mkpath(filename.mid(4, -1));
        }
    }

    while (curCounter < duration) {
        curCounter++;
        img = vtools->seekNextFrame();

        if (img != NULL) {

            //image writing to disk
            if (frameToSkip != 0) {
                if (curCounter % frameToSkip != 0) {
                    /* don */
                } else {
                    img->save(filename + "img"
                              + QString("%1").arg(vtools->getCurrentFrameIndex()) + ext);
                }
            }

            //key timing registering & image buffering
            if (vtools->isCurrentFrameValid()) { //this is obvious here, but in case of weird situations
                emit newValidFrame(vtools->getCurrentTs());
                imageEater.feed(img);
            }

            //image displaying
            emit redraw();

            //renderTarget->show();
            //renderTarget->repaint(); --switched to slot<->signal
        }
    }

    char buff[100];
    sprintf_s(buff, "current raw frame : %d (%d)", vtools->getCurrentFrameIndex()
              , vtools->getCurrentTs());
    QString* result = new QString(buff);
    qDebug() << result;

    imageEater.close();

    emit resultReady(result);
}

void WorkerThread::setTiming(int bwFrames, int duration)
{
    this->bwFrames = bwFrames;
    this->duration = duration;
}

void WorkerThread::setOutputDir(const QString &outputDir)
{
    filename = outputDir;
}
