#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>

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

void MainWindow::on_btClose_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btOpen_clicked()
{
    printf("Test...");
    QString res = QFileDialog::getOpenFileName(this, "Open video file", QDir::homePath());
    ui->txtFile->setText(res);
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
    QImage* img;
    img = vtools.seekNextFrame();
    char buff[100];
    sprintf_s(buff, "rendered : %p", (void*)img);
    logText(buff);
    ui->lblImage->setPixmap(QPixmap::fromImage(*img));
    ui->lblImage->show();
    delete img;
}

void MainWindow::logText(QString text)
{
    ui->txtInfo->setPlainText(ui->txtInfo->toPlainText() + "\r\n" + text);
   // ui->txtInfo->ensureCursorVisible();
    ui->txtInfo->verticalScrollBar()->setValue(ui->txtInfo->verticalScrollBar()->maximum());
}
