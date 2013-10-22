#ifndef IMAGEEATERTHREAD_H
#define IMAGEEATERTHREAD_H

#include <QThread>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QImage>
#include <QLabel>
#include <QPixmap>

class ImageEaterThread : public QThread
{
    Q_OBJECT
public:
    ImageEaterThread(QObject *parent = 0, QLabel *renderTarget = 0);

    void run() Q_DECL_OVERRIDE;

    void feed(QImage* image);
    QImage* eat();

    void wakeup();
    void close();

    void setRate(ulong rate) {
        m_rate = rate;
    }

    void setBufferSize(uint size) {
        m_bufferSize = size;
    }

    int getBufferUtilization() {
        return m_numberImage;
    }

signals:
    void imageEaten(void);

private:
    Q_DISABLE_COPY(ImageEaterThread)
    QList<QImage*> m_buffer;
    QLabel* m_renderTarget;
    bool m_alive;

    mutable QMutex m_mutexFeed;
    mutable QMutex m_mutexEmptyBuffer;
    mutable QMutex m_mutexSleep;
    QWaitCondition m_condition;
    ulong m_rate;
    uint m_bufferSize;
    int m_numberImage;
};

#endif // IMAGEEATERTHREAD_H
