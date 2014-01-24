#ifndef ANALYZER_H
#define ANALYZER_H

#include <QThread>
#include <QFile>
#include <QGraphicsScene>
#include <QStringBuilder>

#include "textprocessing.h"

#include <QDebug>

class Analyzer : public QObject
{
    Q_OBJECT

private:
    bool m_finished;

    //MainWindow& m_main;
    TextProcessing* m_tproc;

    QGraphicsScene* m_scene;
    int m_maxx, m_maxy;
    int m_maxparticle;
    int m_count;
    int m_mod;
    QFile* m_file;


    bool matlabFormat() {
        /*
         * Matlab format for curve clustering requires cell array
         * output will be in curve.txt
         */

        if (m_file == NULL) {
            m_file = new QFile("curve.txt");
            if (m_file->exists()) {
                m_file->remove();
            }
            if (!m_file->open(QIODevice::WriteOnly)) {
                qDebug() << "Cannot open curve.txt";
                m_file = NULL;
                return false;
            }
        }

        TextProcessing::Particle p;
        bool ok = m_tproc->getNextParticle(p);
        if (!ok) { return ok; }

        QString line;
        for (int i = 0; i < p.positionsCount - 1; i++) {
            line = line % QString::number(p.positions[i]) % ",";
        }
        line = line % QString::number(p.positions[p.positionsCount - 1]) % "\r\n";

        m_file->write(line.toStdString().data());

        return true;
    }

    bool sceneFormat(bool& needResize) {
        needResize = false;
        TextProcessing::Particle p;
        bool ok = m_tproc->getNextParticle(p);
        if (!ok) { return ok; }
        //qDebug() << TextProcessing::particleToString(p);

        QPen pen(Qt::blue);
        pen.setWidthF(0.2f);

        bool hasChanged = false;
        int max = p.positionsCount;
        if (max <= 3) {
            //m_scene.addRect(p.start, p.positions[0], 1, 1, pen);
        } else {
            float distx, disty, lastdist, newdist;
            distx = p.positions[0] - p.positions[2];
            disty = p.positions[1] - p.positions[3];
            lastdist = sqrt(distx * distx + disty * disty);

            for (int i = 2; i <= max - 4; i += 2) {

                distx = p.positions[i] - p.positions[i + 2];
                disty = p.positions[i + 1] - p.positions[i + 3];
                newdist = sqrt(distx * distx + disty * disty);
                m_scene->addLine(  p.start + i/2 - 1 //x1
                                , lastdist //y1
                                , p.start + i/2 //x2
                                , newdist, pen); //y2

    //            qDebug() << "(" << p.start + i/2 - 1 << "," << lastdist << ")<->(" << p.start + i/2
    //                     << ", " << newdist << ")";

                if (m_maxy < lastdist) { m_maxy = lastdist; hasChanged = true; }
                lastdist = newdist;

                if (m_maxx < p.start + i/2 - 1) { m_maxx = p.start + i/2 - 1; hasChanged = true; }
                if (m_maxy < newdist) { m_maxy = newdist; hasChanged = true; }

            }

    ////            m_scene.addLine(p.positions[i], p.positions[i + 1],
    ////                    p.positions[i + 2], p.positions[i + 3], pen);
    ////            qDebug() << "p1(" << p.positions[i]
    ////                         << "," << p.positions[i+1]
    ////                            << ") <-> p2(" << p.positions[i+2]
    ////                               << "," << p.positions[i+3] << ")";
    //        }
        }

        if (hasChanged) {
            //m_scene->setSceneRect(0, 0, m_maxx, m_maxy);
            needResize = true;
//            ui->graphicsView->fitInView(m_scene->sceneRect());
        }

        //lower the memory each 5000 items
    //    if (m_count % 5000 == 0) {
    //        QPixmap pix(m_scene.width(), m_scene.height());
    //        QPainter painter(&pix);
    //        painter.setRenderHint(QPainter::Antialiasing);
    //        m_scene.render(&painter);
    //        m_scene.clear();
    //        m_pix = m_scene.addPixmap(pix);
    //    }

        return true;
    }

    bool processNextEntry(bool& needResize) {
        switch (m_mod) {
        case Draw:
            return sceneFormat(needResize);
            break;
        case ToFile:
            needResize = false;
            return matlabFormat();
        }
        return false;
    }

signals:
    void needResize(int width, int height);
    void entryProcessed();
    void finished();

public:
    Analyzer(TextProcessing* tproc, QGraphicsScene* scene, QObject* parent = 0) :
       //m_main(*((MainWindow*) parent))
      m_tproc(tproc)
     , m_scene(scene)
     , m_finished(false)
     , m_maxx(0)
     , m_maxy(1)
     , m_count(0)
     , m_mod(Draw)
     , m_file(NULL)
    {
    }

    void setMod(int mod) { m_mod = mod; }

    void analyze() {
        m_finished = false;
        bool needResize_;
        while (processNextEntry(needResize_)) {
            emit entryProcessed();
            if (needResize_) {
                emit needResize(m_maxx, m_maxy);
            }
            m_count++;
        };
        m_finished = true;
        emit finished();
    }

    bool isFinished() { return m_finished; }
    bool processNextEntry() {
        bool needResize_ = false;
        processNextEntry(needResize_);
        emit entryProcessed();
        if (needResize_) {
            emit needResize(m_maxx, m_maxy);
        }
        m_count++;
        return needResize_;
    }

    enum AnalyzeMod {
        Draw, ToFile
    };
};

#endif // ANALYZER_H
