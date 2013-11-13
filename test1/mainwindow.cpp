#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTime>
#include <QThread>

#include "opticalflowtools.h"

#include "qmlregister.h"

#include <QtQuick/QQuickView>

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , worker(NULL)
  , imageEater(NULL)
  , spline(NULL)
  , m_optflowtools(NULL)
  , timer(this)
  , m_interpUi(NULL)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
}

MainWindow::~MainWindow()
{
    if(worker != NULL) {
        worker->close();
    }
    delete ui;
}

void MainWindow::handleResult(const QString *res)
{
    logText(res);
//    char buff[100];
//    sprintf_s(buff, "current dts : %d (%d)", vtools.getCurrentDts(), vtools.getCurrentTs());
//    QString* result = new QString(buff);
//    logText(result);
}

void MainWindow::handleNewValidFrame(qlonglong time)
{
    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    spline->addKey(time, time);
   // logText(&QString("ts : %1").arg(time));
}

///
/// \brief MainWindow::threadFinished
///Worker has finished.
void MainWindow::threadFinished()
{
    timer.stop();
    worker = NULL;
    imageEater = NULL;
}

void MainWindow::handleImageEaten()
{
    /* don */
}

void MainWindow::handleTimeout()
{
    //routines
    if(imageEater != NULL) {
        ui->pbBuffer->setValue(imageEater->getBufferUtilization());
        logText(&QString("current ts : %1").arg(vtools.getCurrentTs()));
    }

    if(spline != NULL) {
        spline->setplayposition(vtools.getCurrentTs());
    } else {
        //try applying value
        spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
        if(spline == 0) {
            spline = NULL;
        }
    }
    //too heavy
//    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    //    spline->update();
}

void MainWindow::handleNeedSequences(QList<Sequence *>& sequences)
{
    if (spline != NULL) {
        sequences = spline->getSequences();
    }
}

void MainWindow::on_btClose_clicked()
{
    if(worker != NULL) {
        worker->close();
    }
    QApplication::quit();
}


void MainWindow::on_btOpen_clicked()
{
    dc = 0;
    QString res = QFileDialog::getOpenFileName(this, "Open video file", QDir::homePath());
    ui->txtFile->setText(res); 
}

//void MainWindow::initVtools(const QString& filename) {

//}

void MainWindow::on_btGo_clicked()
{
    if(worker != NULL) {
        return;
    }

    QString txtContent = ui->txtFile->text();
    if (filename.isEmpty() || txtContent.compare(filename) != 0) {
        filename = txtContent;
        //VideoTools::getMediaInfo(res);
        //VideoTools::testFfmpeg(res);

        //TODO : deallocate resources if vtools already exists
        vtools = VideoTools();

        int out;
        out = vtools.initFfmpeg(filename);
        //qDebug("initFfmpeg : %d", out);
        logText(&QString("FFmpeg initialized. Video length : %1 ms").arg(vtools.getDurationMs()));

        //add two points for the spline
        SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");

        spline->setduration(vtools.getDurationMs());
        spline->initView();
    } else {
        if (filename.isEmpty()) {
            logText("No source");
            return;
        }
    }

    //interconnect elements
    vtools.setFramesToSkip(ui->txtSkipFrames->text().toInt());
    if (imageEater != NULL) { imageEater->close(); delete imageEater; }
    imageEater = new ImageEaterThread(this, ui->lblImage);
    imageEater->setRate(ui->slSpeed->value());
    ui->pbBuffer->setValue(0);
    imageEater->setBufferSize(ui->cboBuffer->currentText().toInt());
    ui->pbBuffer->setMaximum(ui->cboBuffer->currentText().toInt());
    WorkerThread *workerThread = new WorkerThread(this, ui->lblImage, &vtools, *imageEater);
    workerThread->setTiming(ui->txtFrame->text().toInt(), ui->txtDuration->text().toInt());
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResult);
    connect(workerThread, &WorkerThread::newValidFrame, this, &MainWindow::handleNewValidFrame);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    connect(workerThread, &WorkerThread::finished, this, &MainWindow::threadFinished);

    //we don't need this one because finish event is handled in the workerThread
    //connect(imageEater, &ImageEaterThread::finished, imageEater, &QObject::threadFinished);

    connect(imageEater, SIGNAL(imageEaten()), this, SLOT(handleImageEaten()));

    //repaint
    connect(workerThread, SIGNAL(redraw()), ui->lblImage, SLOT(repaint()));
    //------
    workerThread->start();
    worker = workerThread;

    timer.start(500);
}

//void MainWindow::logText(const char* text) {
//    logText(&QString(text));
//}

void MainWindow::logText(const QString *text)
{
    QString plainText = ui->txtInfo->toPlainText();
    if (plainText.length() > 1000) {
        plainText.truncate(500);
    }
    ui->txtInfo->setPlainText(plainText + "\r\n" + *text);
    ui->txtInfo->verticalScrollBar()->setValue(ui->txtInfo->verticalScrollBar()->maximum());
}

void MainWindow::on_btFlow_clicked()
{

    m_optflowtools = OpticalFlowTools::createWindow(this);
    if (spline != NULL) {
        m_optflowtools->setSequences(spline->getSequences());
    }

    /* QML version not used
     *
    OpticalFlowTools* m_optflowtools = (OpticalFlowTools*) QMLRegister::getQMLObject("optflowtools");
    optflowtools->initializeTools();
   */

    //tests
//    ui->->loadImages("img1.jpg", "img2.jpg");
//    //compute coarse2fine
//    QImage& image = *OpticalFlowTools::computeCoarse2Fine("car1.jpg", "car2.jpg");
//    //ui->wOpticalFlow->loadImOut(image);
//    ui->wOpticalFlow->loadImOut("flowout.jpg");
    //delete image;
}

void MainWindow::on_btTimeline_clicked()
{
    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    spline->beginAddSequence();

}

void MainWindow::on_slSpeed_sliderMoved(int position)
{
    if(imageEater != NULL) {
        imageEater->setRate(position);
    }
}

void MainWindow::on_cboBuffer_currentTextChanged(const QString &arg1)
{
    if(imageEater != NULL) {
        int value = arg1.toInt();
        imageEater->setBufferSize(value);
        ui->pbBuffer->setMaximum(value);
    }
}


void MainWindow::on_slSpeed_sliderReleased()
{
    logText(&QString("speed : %1").arg(ui->slSpeed->value()));
}

void MainWindow::on_btInterpolate_clicked()
{
    InterpolateUi* interpui = new InterpolateUi();
    connect(interpui, &InterpolateUi::needSequences, this, &MainWindow::handleNeedSequences);
    interpui->show();
}
