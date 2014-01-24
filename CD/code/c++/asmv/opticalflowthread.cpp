#include "opticalflowthread.h"

#include "utils/filesutils.h"

#include <QDebug>
#include <QDir>

OpticalFlowThread::OpticalFlowThread(OpticalFlowTools* optflowtools, QObject* parent)
    : QThread(parent)
    , m_optflowtools(optflowtools)
    , m_pause(false)
    , m_alive(true)
    , m_running(false)
{
}

void OpticalFlowThread::run() {
    qDebug() << "Optflow thread started.";
    if (m_inputDir.isEmpty() || m_outputDir.isEmpty()) {
        qDebug() << "Dirs incorrect.";
        return;
    }

    QDir dirin(m_inputDir);
    if (!dirin.exists()) {
        qDebug() << "Input dir does not exist.";
        return;
    }

    QFileInfoList images = dirin.entryInfoList(getSupportedImagesFilter()
                                               , QDir::Files
                                               , QDir::Name);
    sortFiles(images);

    QImage* img1;
    QImage* img2;
    QImage* flow;
    img1 = NULL;
    img2 = NULL;
    QString filename1;
    m_running = true;
    int counter(0);
    while (m_alive) {
        foreach (QFileInfo file, images) {
            if (m_pause) {
                m_mutexSleep.lock();
                m_condition.wait(&m_mutexSleep);
                m_mutexSleep.unlock();
            }
            if (!m_alive) {
                break;
            }

            QString filename2 = QString("%1%2").arg(m_inputDir, file.fileName());
            //compute optical flow
            if (img1 == NULL) {
                img1 = new QImage(filename2);
                filename1 = filename2;
                continue;
            }
            qDebug() << "image1 : " << filename1 << " image2 : " << filename2;
            img2 = new QImage(filename2);
            flow = m_optflowtools->computeFlow(img1, img2
                                        , filename1
                                        , filename2);

            //emit result
            float perc = (float)(counter + 1) / (float)images.size() * 100.f;
            emit flowComputed(img1, img2, flow, ceil(perc));
            counter++;

            //manage images
            img1 = img2;
            filename1 = filename2;
        }
        emit flowComputed(NULL, NULL, NULL, 100);
        m_alive = false;
    }
    qDebug() << "Optflow thread ended.";
    m_running = false;
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

bool OpticalFlowThread::isRunning()
{
    return m_running;
}
