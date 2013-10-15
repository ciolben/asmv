#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTime>
#include <QThread>

#include "workerthread.h"
#include "opticalflowtools.h"
#include "timeline.h"

#include "qmlregister.h"

#include <QtQuick/QQuickView>

#include <stdio.h>

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

void MainWindow::handleResult(const QString *res)
{
    logText(res);
}

void MainWindow::on_btClose_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btOpen_clicked()
{
    printf("Test...");
    dc = 0;
    QString res = QFileDialog::getOpenFileName(this, "Open video file", QDir::homePath());
    ui->txtFile->setText(res);
    //TODO : read content of text before initializing vtools
    if (!res.isEmpty()) {
        filename = res;
        //VideoTools::getMediaInfo(res);
        //VideoTools::testFfmpeg(res);
        vtools = VideoTools();

        int out;
        out = vtools.initFfmpeg(filename);
        qDebug("initFfmpeg : %d", out);
        logText("FFmpeg initialized.");
    }
}

void MainWindow::on_btGo_clicked()
{
    vtools.setFramesToSkip(ui->txtSkipFrames->text().toInt());
    WorkerThread *workerThread = new WorkerThread(this, ui->lblImage, &vtools);
    workerThread->setTiming(ui->txtFrame->text().toInt(), ui->txtDuration->text().toInt());
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResult);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    //repaint
    connect(workerThread, SIGNAL(redraw()), ui->lblImage, SLOT(repaint()));
    //------
    workerThread->start();
}

//void MainWindow::logText(const char* text) {
//    logText(&QString(text));
//}

void MainWindow::logText(const QString *text)
{
    ui->txtInfo->setPlainText(ui->txtInfo->toPlainText() + "\r\n" + *text);
    ui->txtInfo->verticalScrollBar()->setValue(ui->txtInfo->verticalScrollBar()->maximum());
}

void MainWindow::on_btFlow_clicked()
{
//    ui->wOpticalFlow->loadImages("img1.jpg", "img2.jpg");
//    //compute coarse2fine
//    QImage& image = *OpticalFlowTools::computeCoarse2Fine("img1.jpg", "img2.jpg");
//    //ui->wOpticalFlow->loadImOut(image);
//    ui->wOpticalFlow->loadImOut("flowout.jpg");
    //delete image;
}

void MainWindow::on_btTimeline_clicked()
{
    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    spline->addKey(0, 0);
    spline->addKey(20, 20);
    spline->addKey(40, 40);
    spline->addKey(60, 80);
    spline->addKey(80, 110);
    spline->addKey(100, 140);
    spline->addKey(120, 170);
    spline->addKey(140, 200);
    spline->addKey(160, 220);
    spline->addKey(180, 240);
    spline->addKey(200, 260);
    spline->addKey(220, 280);
    spline->addKey(240, 300);
    spline->addKey(260, 320);
    spline->addKey(280, 340);
    spline->addKey(300, 360);

}
