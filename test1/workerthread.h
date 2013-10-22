#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QLabel>

#include "videotools.h"
#include "imageeaterthread.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent, QLabel *renderTarget, VideoTools *vTools, ImageEaterThread& _imageEater);

    void run() Q_DECL_OVERRIDE;
    void close();

    void setTiming(int bwFrames, int duration);

signals:
    void resultReady(const QString* s);
    void newValidFrame(qlonglong time);
    void redraw(void);

public slots:

private:
    QLabel* renderTarget;
    VideoTools* vtools;

    int bwFrames;
    int duration;

    ImageEaterThread& imageEater;

    QString filename;
};

#endif // WORKERTHREAD_H
