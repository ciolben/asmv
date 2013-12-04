#ifndef MOTIONTHREAD_H
#define MOTIONTHREAD_H

#include <QThread>
#include <QFlags>

//PARAMETERS
//***************
///
/// \brief _minThreshold
///     The min value for which the displacement is saved.
///
const float _minThreshold = 0.5f;

///
/// \brief _maxDistInsideCluster
///     Maximum distance allowed between points in one cluster.
///
const float _maxDistInsideCluster = 0.5f;

///
/// \brief _minClusterSize
///     Minimum cluster size.
///
const float _minClusterSize = 10;
//***************

class MotionThread : public QThread
{
    Q_OBJECT
public:
    explicit MotionThread(QObject *parent = 0);
    explicit MotionThread(const QString& filename, QObject *parent = 0);

    enum Step { None = 0x0, Affine = 0x1, wflow = 0x2, Profile = 0x4 };
    Q_DECLARE_FLAGS(Steps, Step)
    enum DebugFlag { WSorted = 0x1, WClust = 0x2 };
    Q_DECLARE_FLAGS(DebugFlags, DebugFlag)

    void setSteps(Steps steps);
    void setDebug(DebugFlags debugFlags) {}; //TODO
    void setParameters() {}; //TODO

    void close();

    void run();

    typedef QMap<float, int> motions;

signals:
    void logText(const QString& info, const QString& color = "", bool bold = false, bool italic = false);

public slots:

private:
    QString m_filename;
    Steps m_steps;
    bool m_continue;

    struct cluster {
        float start;
        float end;
        float avg;
        int size;
    };

    ///
    /// \brief The Clusterizer class
    ///     Class used for clusterizing a part of the key list.
    class Clusterizer {
    private:
        const QList<float>& m_keys;
        const int m_begin;
        const int m_end;
        QList<cluster>& m_result;

    public:
        Clusterizer(const QList<float>& keys, QList<cluster>* result, const int begin, const int end) :
            m_keys(keys), m_result(*result), m_begin(begin), m_end(end)
        {
        }

        void clusterize() {
            QList<float> currentClusterValues;
            cluster currentCluster;

            float lastKey = m_keys.at(m_begin);
            float currentKey;

            currentCluster.start = lastKey;
            currentClusterValues.append(lastKey);

            for (int i = m_begin + 1; i < m_end; i++) {
                currentKey = m_keys.at(i);
                //test if they are in the same cluster
                if (lastKey - currentKey <= _maxDistInsideCluster) {
                    currentClusterValues.append(currentKey);
                } else {
                    //validate this cluster
                    if (currentClusterValues.size() > _minClusterSize) {
                        float sum = 0;
                        foreach (float f, currentClusterValues) {
                            sum += f;
                        }
                        currentCluster.size = currentClusterValues.size();
                        currentCluster.avg = sum / currentClusterValues.size();
                        currentCluster.end = currentKey;

                        m_result.append(currentCluster);
                    }

                    currentClusterValues.clear();
                    if (i + 1 > m_end) {
                        break;
                    }
                    currentCluster.start = m_keys.at(i + 1);
                    currentClusterValues.append(currentKey);

                }

                lastKey = currentKey;
            }
            //validate last cluster
            if (currentClusterValues.size() > _minClusterSize) {
                float sum = 0;
                foreach (float f, currentClusterValues) {
                    sum += f;
                }
                currentCluster.size = currentClusterValues.size();
                currentCluster.avg = sum / currentClusterValues.size();
                currentCluster.end = currentKey;
                m_result.append(currentCluster);
            }
        }
    };
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MotionThread::Steps)
#endif // MOTIONTHREAD_H