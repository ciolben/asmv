#include "imageeaterthread.h"

#include <QDebug>

ImageEaterThread::ImageEaterThread(QObject *parent, QLabel *renderTarget) :
    QThread(parent)
    , m_renderTarget(renderTarget)
    , m_buffer(QList<QImage*>())
    , m_alive(true)
    , m_rate(1000)
    , m_bufferSize(0)
    , m_numberImage(0)
{

}

///
/// \brief ImageEaterThread::feed
/// Block if buffer is full.
/// \param image
///
void ImageEaterThread::feed(QImage* image) {
    if(m_numberImage >= m_bufferSize) {
        m_mutexEmptyBuffer.lock();
        m_condition.wait(&m_mutexEmptyBuffer);
        m_mutexEmptyBuffer.unlock();
    }

    QMutexLocker locker(&m_mutexFeed);
    m_numberImage++;
    m_buffer.append(image);
}

QImage* ImageEaterThread::eat() {
    QMutexLocker locker(&m_mutexFeed);
    if (m_buffer.isEmpty()) {
        return NULL;
    }
    m_numberImage--;
    QImage* res = m_buffer.first();
    m_buffer.removeFirst();
    return res;
}

void ImageEaterThread::wakeup() {
    m_condition.wakeAll();
}

void ImageEaterThread::close() {
    m_alive = false;
    QMutexLocker locker(&m_mutexFeed);
    foreach (QImage* img, m_buffer) {
        delete img;
    }
    m_buffer.clear();
    wakeup();
}

void ImageEaterThread::run() {
    QImage* image;
    m_alive = true;
    while(m_alive) {
        m_mutexSleep.lock();
        m_condition.wait(&m_mutexSleep, m_rate);
        m_mutexSleep.unlock();
        image = eat();
        if (image != NULL && m_alive) {
            // TODO : when main window dies, m_renderTarget is deallocated
            // shared mutex ? (testing for m_alive is not sufficient)
            m_renderTarget->setPixmap(QPixmap::fromImage(*image));

            //allows for dynamic buffersize change and more robust when heavy lag
            if(m_numberImage < m_bufferSize) {
                m_condition.wakeAll();
            }

            delete image;
            emit imageEaten();
        }
    }
}
