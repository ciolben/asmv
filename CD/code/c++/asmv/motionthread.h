#ifndef MOTIONTHREAD_H
#define MOTIONTHREAD_H

#include <QThread>
#include <QFlags>
#include <QStringList>

#include <vector>

Q_DECLARE_METATYPE(std::vector<float>)

//PARAMETERS
//***************
extern float _minThreshold;
extern float _maxThreshold;
extern float _maxDistInsideCluster;
extern float _minClusterSize;
extern float _windowSizeFirstPass;
extern float _windowSizeSecondPass;
extern bool _adaptive;

//***************
#include <QFile>
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

    enum OtherFlag { NoOther = 0x0, WriteMotion = 0x1 };
    Q_DECLARE_FLAGS(OtherFlags, OtherFlag)

    void setSteps(Steps steps);
    void setDebug(DebugFlags debugFlags) {}; //TODO
    void setParameters() {}; //TODO
    void setOthers(OtherFlags flags);
    void addFilesFilters(QString filter);
    void setSmootingIntensity(int smoothing);
    void setErrorThreshold(float value);

    void close();

    void run();

    typedef QMap<float, int> motions;

signals:
    void logText(const QString& info, const QString& color = "", bool bold = false, bool italic = false);
    void motionProfileComputed(const QString& filename, std::vector<float> data);
    void dialogGetItems(QStringList* list, QString* out, bool* ok);

public slots:

private:
    QString m_filename;
    QStringList m_filesFilters;
    Steps m_steps;
    OtherFlags m_others;
    bool m_continue;
    int m_smoothingIntensity;
    int m_errorThreshold;

    void initParameters();

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

//            QFile out2(QString("debug%1_%2.txt").arg(lastKey).arg(m_keys.size()));
//            out2.open(QFile::WriteOnly);
//            out2.write("begin\r\n");
//            out2.flush();
//            out2.write(QString("b : %1, e : %2, results : %3, keys : %4").arg(m_begin).arg(m_end).arg(m_result.size()).arg(m_keys.size()).toLocal8Bit().constData());
//            out2.flush();

            for (int i = m_begin + 1; i < m_end; i++) {
                currentKey = m_keys.at(i);
                //test if they are in the same cluster
            //    out2.write((QString("%1 - %2 < %3 : %4").arg(lastKey).arg(currentKey)
            //                .arg(_maxDistInsideCluster).arg((lastKey - currentKey <= _maxDistInsideCluster))).toLocal8Bit().constData());
                if (currentKey - lastKey <= _maxDistInsideCluster) {
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
                    if (i + 1 >= m_end) {
                        break;
                    }
                    currentCluster.start = m_keys.at(i + 1);
                    currentClusterValues.append(currentKey);
                }

                if (_adaptive) { lastKey = currentKey; }
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
