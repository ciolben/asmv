#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTime>
#include <QThread>
#include "workerthread.h"

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

void MainWindow::handleResult(QString *res)
{
    //don
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
//    QImage* img;
//    int curCounter = 0;

//    QTime time;
//    time.start();
//    while (curCounter < 1) {
//        curCounter++;
//        dc++;
//        img = vtools.seekNextFrame();

//        if (img == NULL) {
//            logText("NULL frame");
//        } else {
//            char buff[100];
//            sprintf_s(buff, "rendered : %p (%d)", (void*)img, dc);
//            logText(buff);
//            ui->lblImage->setPixmap(QPixmap::fromImage(*img));
//            ui->lblImage->show();
//            delete img;
//        }

//        this->thread()->sleep(1); //1000/24 =~ 42
//    }

    //new implemtation with thread
    WorkerThread *workerThread = new WorkerThread(this, ui->lblImage, &vtools);
    workerThread->setTiming(ui->txtFrame->text().toInt(), ui->txtDuration->text().toInt());
    //connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResult);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();

}

void MainWindow::logText(QString text)
{
    ui->txtInfo->setPlainText(ui->txtInfo->toPlainText() + "\r\n" + text);
   // ui->txtInfo->ensureCursorVisible();
    ui->txtInfo->verticalScrollBar()->setValue(ui->txtInfo->verticalScrollBar()->maximum());
}
