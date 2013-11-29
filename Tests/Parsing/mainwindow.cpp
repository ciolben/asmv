#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMediaPlayer"
#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QList>
#include <QByteArray>

struct cluster {
    float start;
    float end;
    float avg;
    int size;
};

void MainWindow::on_pushButton_clicked()
{
//    QMediaPlayer qplayer (new QMediaPlayer());
//    qplayer.setMedia(QMediaContent(QUrl::fromLocalFile("file")));
//    qplayer.play();
//    QMediaResource resource = qplayer.media().canonicalResource();
//    qDebug() << "a_bitrate : " << resource.audioBitRate();
//    qDebug() << "other prop : " << resource.videoBitRate();

    qDebug() << "Push";
//    QByteArray ba("%YAML:1.0\n"
//                  "wflow: !!opencv-matrix\n"
//                     "rows: 120\n"
//                  "cols: 160\n"
//                  "dt: \"2f\"\n"
//                  "data: [ -3.92618254e-002, -2.60025356e-002, -3.91570330e-002,\n"
//                  "-2.60888077e-002, -3.90552133e-002, -2.61752736e-002,\n"
//                  "-3.89544554e-002, -2.62610167e-002, -3.88523303e-002,\n"
//                  "-2.63459645e-002, -3.87486480e-002, -2.64311191e-002,\n"
//                         "-3.86440530e-002, -2.65167728e-002, -3.85393724e-002 ]\n");
//    int length = ba.size();
//    int dataBegin = ba.indexOf("[ ") + 1;
//    int cut = (length - dataBegin) / 4;
//    char sep = ',';
//    int last = dataBegin;
//    QList<QByteArray> ars;
//    for (int i = dataBegin + cut; i < length; i++) {
//        if (ba.at(i) == sep) {
//            ars.append(ba.mid(last + 1, i - last - 1));
//            last = i + 1;
//            i += cut;
//            if (i >= length) { // we are cutting a too big piece, this is the last one
//                ars.append(ba.mid(last, length - last - 3)); //without " ]"
//            }
//        }
//    }

//    int ct = 0;
//    foreach (QByteArray ar, ars) {
//        qDebug() << ct << " : " << ar;
//        ct++;
//    }

    QList<float> m_keys;
     int m_begin;
     int m_end;


    float _maxDistInsideCluster = ui->txtdist->text().toFloat();
    float _minClusterSize = ui->txtclust->text().toFloat();

    QFile file("input.txt");
    file.open(QFile::ReadOnly);
    QByteArray b = file.readAll();
    QTextStream stream(b);

    while (!stream.atEnd()) {
        QString s = stream.readLine();
        m_keys.append(s.toFloat());
    }
    file.close();

    int nbThread = ui->txtNbThread->text().toInt(), pass = 0;
    int range = m_keys.size() / nbThread;

    QList<QList<cluster>> results;

loop:
    m_begin = pass * range;
    m_end = pass * range + range;

    ++pass;

    if (pass == nbThread) { m_end = m_keys.size(); }

    QList<cluster> m_result;

    QList<float> currentClusterValues;
    cluster currentCluster;

    float lastKey = m_keys.at(m_begin);
    lastKey = (lastKey < 0) ? -lastKey : lastKey;
    float currentKey;

    currentCluster.start = lastKey;
    currentClusterValues.append(lastKey);

    for (int i = m_begin + 1; i < m_end; i++) {
        currentKey = m_keys.at(i);
        currentKey = currentKey < 0 ? -currentKey : currentKey;
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

    qDebug() << "**pass : " << pass << " **";
    foreach (cluster c, m_result) {
        qDebug() << "s : " << c.start <<  " e : " << c.end <<  " a : " << c.avg << " sz : " << c.size;
    }

    results.append(m_result);

    if (pass != nbThread) {
        goto loop;
    }

    QList<cluster> result;
    foreach (QList<cluster> clustList, results) {
        for (int i = 0; i < clustList.size(); ++i) {
            if (i == 0 && result.size() != 0) {
                cluster c1 = result.last(); result.removeLast();
                cluster c2 = clustList.at(i);
                if (c2.start - c1.end < _maxDistInsideCluster) {
                    cluster c12;
                    c12.start = c1.start;
                    c12.end = c2.end;
                    c12.size = c1.size + c2.size;
                    c12.avg = (c1.avg * c1.size + c2.avg * c2.size) / c12.size;
                    result.append(c12);
                }
            } else {
                result.append(clustList.at(i));
            }
        }
    }

    qDebug() << "*********************";
    foreach (cluster c, result) {
        qDebug() << "s : " << c.start <<  " e : " << c.end <<  " a : " << c.avg << " sz : " << c.size;
    }
}
