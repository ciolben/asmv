#include "workerthread.h"

#include <QTime>
#include <QStringBuilder>

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{
    //constructoor
}

WorkerThread::WorkerThread(QObject *parent, QLabel *renderTarget, VideoTools* vTools)
    : QThread(parent)
    , renderTarget(renderTarget)
    , vtools(vTools)
    , bwFrames(0)
    , duration(0)
    , filename("out/")
{

}

void WorkerThread::run() {
    QImage* img;
    QTime time;
    QString ext = ".jpg";

    int curCounter = 0;
    int frameToSkip = vtools->getFramesToSkip();

    time.start();
    while (curCounter < duration) {
        curCounter++;
        img = vtools->seekNextFrame();

        if (img == NULL) {
            //logText("NULL frame");
        } else {
            //char buff[100];
            // sprintf_s(buff, "rendered : %p (%d)", (void*)img, dc);
           // emit resultReady(new QString(buff));	
//            logText(buff);

            if (curCounter % frameToSkip != 0) {
                /* don */
            } else {
                renderTarget->setPixmap(QPixmap::fromImage(*img));
                emit redraw();
                img->save(filename + "img"
                          + QString("%1").arg(vtools->getCurrentFrameIndex()) + ext);
            }

            //renderTarget->show();
            //renderTarget->repaint(); --switched to slot<->signal

            //img->save(filename + "img" + QString("%1").arg(dc) + ext);
        }
		delete img;
        this->thread()->msleep(bwFrames); //1000/24 =~ 42
    }

    char buff[100];
    sprintf_s(buff, "ok (%d)", vtools->getCurrentFrameIndex());
    QString* result = new QString(buff);
    emit resultReady(result);
}

void WorkerThread::setTiming(int bwFrames, int duration)
{
    this->bwFrames = bwFrames;
    this->duration = duration;
}
