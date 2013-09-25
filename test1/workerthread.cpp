#include "workerthread.h"

#include <QTime>

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
{

}

void WorkerThread::run() {
    QImage* img;
    QTime time;
    int curCounter = 0;

    time.start();
    while (curCounter < duration) {
        curCounter++;
        //dc++;
        img = vtools->seekNextFrame();

        if (img == NULL) {
            //logText("NULL frame");
        } else {
//            char buff[100];
//            sprintf_s(buff, "rendered : %p (%d)", (void*)img, dc);
//            logText(buff);
            renderTarget->setPixmap(QPixmap::fromImage(*img));
            renderTarget->show();
            delete img;
        }
        this->thread()->msleep(bwFrames); //1000/24 =~ 42
    }

    //emit resultReady("result");
}

void WorkerThread::setTiming(int bwFrames, int duration)
{
    this->bwFrames = bwFrames;
    this->duration = duration;
}
