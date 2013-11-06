#include "opticalflowthread.h"

#include <QDebug>
#include <QDir>

OpticalFlowThread::OpticalFlowThread(QObject* parent, )
    : QThread(parent)
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
        if (!QDir::mkdir(m_outputDir)) {
            qDebug() << "Cannot creat output dir.";
            return;
        }
    }

    QFileInfoList images = dirin.entryInfoList(QDir::Files);
    QStringList exts = {"jpg", "jpeg", "png"};

    QImage* img1 = NULL, img2 = NULL, flow;
    bool isImage = false;
    while (m_alive) {
        foreach (QFileInfo file, images) {
            if (m_pause) {
                m_mutexSleep.lock();
                m_condition.wait(m_mutexSleep);
                m_mutexSleep.unlock();
            }

            foreach (String ext, exts) {
                if (file.suffix().compare(ext)) {
                    isImage = true; break;
                }
            }
            if (!isImage) { continue; } else { isImage = false; }

            //compute optical flow
            if (img1 == NULL) {
                img1 = new QImage(m_inputDir.append(file));
                continue;
            }
            img2 = new QImage(m_inputDir.append(file));
            m_optflowtools->computeFlow(img1, img2, flow);

            //emit result
            emit flowComputed(img1, img2, flow);

            //manage images
            img1 = img2;
        }

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
