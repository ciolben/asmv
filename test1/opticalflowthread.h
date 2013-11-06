#ifndef OPTICALFLOWTHREAD_H
#define OPTICALFLOWTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>

#include "opticalflowtools.h"

class OpticalFlowThread : public QThread
{
    Q_OBJECT
public:
    OpticalFlowThread(QObject *parent = 0, OpticalFlowTools* optflowtools);

    void run() Q_DECL_OVERRIDE;

    void pause();
    void resume();
    void stop();

    void setInputDir(QString inputDir) { m_inputDir = inputDir; }
    void setOutputDir(QString outputDir) { m_outputDir = outputDir; }

signals:
    void flowComputed(QImage* img1, QImage* img2, QImage* flow);

private:
    OpticalFlowTools* m_optflowtools;

    mutable QMutex m_mutexSleep;
    QWaitCondition m_condition;

    bool m_pause;
    bool m_alive;

    QString m_inputDir;
    QString m_outputDir;
};

#endif // OPTICALFLOWTHREAD_H