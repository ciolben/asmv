#include "opticalflowthread.h"

#include <QDebug>
#include <QDir>

OpticalFlowThread::OpticalFlowThread(OpticalFlowTools* optflowtools, QObject* parent)
    : QThread(parent)
    , m_optflowtools(optflowtools)
    , m_pause(false)
    , m_alive(true)
{
}

void OpticalFlowThread::run() {
    qDebug() << "Optflow thread started.";
    if (m_inputDir.isEmpty() || m_outputDir.isEmpty()) {
        qDebug() << "Dirs incorrect.";
        return;
    }

    QDir dirin(m_inputDir);
    QDir dirout(m_outputDir);
    if (!dirin.exists()) {
        qDebug() << "Input dir does not exist.";
        return;
    }
    if (!dirout.exists()) {
        if (!dirout.mkpath(m_outputDir)) {
            qDebug() << "Cannot create output dir.";
            return;
        }
    }

    QFileInfoList images = dirin.entryInfoList(QDir::Files);
    QStringList exts; exts << "jpg" << "jpeg" << "png";

    QImage* img1;
    QImage* img2;
    QImage* flow;
    img1 = NULL;
    img2 = NULL;
    QString filename1;
    bool isImage = false;
    while (m_alive) {
        foreach (QFileInfo file, images) {
            if (m_pause) {
                m_mutexSleep.lock();
                m_condition.wait(&m_mutexSleep);
                m_mutexSleep.unlock();
            }

            foreach (QString ext, exts) {
                if (file.suffix().compare(ext)) {
                    isImage = true; break;
                }
            }
            if (!isImage) { continue; } else { isImage = false; }

            QString filename2 = QString("%1%2").arg(m_inputDir, file.fileName());
            //compute optical flow
            if (img1 == NULL) {
                img1 = new QImage(filename2);
                filename1 = filename2;
                continue;
            }
            qDebug() << "image : " << filename2;
            img2 = new QImage(filename2);
            flow = m_optflowtools->computeFlow(img1, img2
                                        , filename1
                                        , filename2);

            //emit result
            emit flowComputed(img1, img2, flow);

            //manage images
            img1 = img2;
            filename1 = filename2;
        }
        m_alive = false;
    }
    qDebug() << "Optflow thread ended.";
}

void OpticalFlowThread::pause()
{
    m_pause = true;
}

void OpticalFlowThread::resume()
{
    m_pause = false;
    m_condition.wakeAll();
}

void OpticalFlowThread::stop()
{
    m_alive = false;
    m_pause = false;
    m_condition.wakeAll();
}
