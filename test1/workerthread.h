#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QLabel>

#include "videotools.h"

class WorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit WorkerThread(QObject *parent = 0);
    explicit WorkerThread(QObject *parent, QLabel *renderTarget, VideoTools *vTools);

    void run() Q_DECL_OVERRIDE;

    void setTiming(int bwFrames, int duration);

signals:
    void resultReady(const QString* s);
    void redraw(void);

public slots:

private:
    QLabel* renderTarget;
    VideoTools* vtools;

    int bwFrames;
    int duration;

    QString filename;
};

#endif // WORKERTHREAD_H
