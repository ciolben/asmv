#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QBrush>

#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_tproc(TextProcessing())
  , m_scene(this)
  , m_maxx(0)
  , m_maxy(1)
  , m_maxparticle(0)
  , m_count(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    //m_maxx = ui->graphicsView->width();
    m_maxy = 10000;
    int number = m_tproc.setContent("C:/Users/Loic/Coding_Main/ADM/pvl/VCars-pv.txt");
    ui->statusBar->showMessage(QString("File : %1 | Number of particles : %2").arg("VCars-pv.txt").arg(number));
    m_maxparticle  = number;

    ui->pbAnalyze->setMaximum(number);
    ui->pbAnalyze->setMinimum(0);
    ui->pbAnalyze->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::processNextEntry()
{
    //qDebug() << "aaaa";
    TextProcessing::Particle p;
    bool ok = m_tproc.getNextParticle(p);
    if (!ok) { return ok; }
    //qDebug() << TextProcessing::particleToString(p);

    QPen pen(Qt::blue);
    pen.setWidth(1);

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
            m_scene.addLine(  p.start + i/2 - 1 //x1
                            , lastdist //y1
                            , p.start + i/2 //x2
                            , newdist); //y2

//            qDebug() << "(" << p.start + i/2 - 1 << "," << lastdist << ")<->(" << p.start + i/2
//                     << ", " << newdist << ")";

            if (m_maxy < lastdist) { m_maxy = lastdist; hasChanged = true; }
            lastdist = newdist;

            if (m_maxx < p.start + i/2 - 1) { m_maxx = p.start + i/2 - 1; hasChanged = true; }
            if (m_maxy < newdist) { m_maxy = newdist; hasChanged = true; }

        }
//        for (int i = 0; i <= max - 4; i += 2) {
//            if (m_maxx < p.positions[i+1]) {
//                m_maxx = p.positions[i+1]; hasChanged = true;
//            }
//            if (m_maxx < p.positions[i+3]) {
//                m_maxx = p.positions[i+3]; hasChanged = true;
//            }
//            if (m_maxy < p.positions[i]) {
//                m_maxy = p.positions[i]; hasChanged = true;
//            }
//            if (m_maxy < p.positions[i+2]) {
//                m_maxy = p.positions[i+2]; hasChanged = true;
//            }

////            m_scene.addLine(p.positions[i], p.positions[i + 1],
////                    p.positions[i + 2], p.positions[i + 3], pen);
////            qDebug() << "p1(" << p.positions[i]
////                         << "," << p.positions[i+1]
////                            << ") <-> p2(" << p.positions[i+2]
////                               << "," << p.positions[i+3] << ")";
//        }
    }

    if (hasChanged) {
        m_scene.setSceneRect(0, 0, m_maxx, m_maxy);
        ui->graphicsView->fitInView(m_scene.sceneRect());
    }

    return true;
}

void MainWindow::handleEnryProcessed()
{
    m_count++;
    ui->pbAnalyze->setValue(m_count);
}

void MainWindow::on_actionOpen_triggered()
{
    QString res = QFileDialog::getOpenFileName(this, "Open sps file", QDir::homePath());
    if (res.isEmpty()) { return; }
    QFile file(res);
    if (!file.exists()) { return;  }

    if (m_tproc.isSet()) {
       /* don */
    }
    int number = m_tproc.setContent(res);
    ui->statusBar->showMessage(QString("File : %1 | Number of particles : %2").arg(file.fileName()).arg(number));
    m_maxparticle = number;
}

void MainWindow::on_actionStart_triggered()
{
    if (processNextEntry()) { ui->graphicsView->update(); }
}

void MainWindow::on_actionClear_triggered()
{
    m_scene.clear();
    m_tproc.resetToBegining();
}

void MainWindow::on_actionStart_2_triggered()
{
    //Start
//    while (processNextEntry()) {
//        ui->graphicsView->update();
//    }

    if (m_count > 0) { return; }
    Analyzer* a = new Analyzer(*ui->graphicsView, this);
    a->start();
    connect(a, &Analyzer::entryProcessed, this, &MainWindow::handleEnryProcessed);

}
