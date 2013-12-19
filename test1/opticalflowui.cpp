#include "opticalflowui.h"
#include "ui_opticalflowui.h"

#include "opticalflowthread.h"

#include <QDebug>

OpticalFlowUI::OpticalFlowUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpticalFlowUI)
  , m_inputDir("")
  , m_outputDir("")
  , m_optflowtools(NULL)
  , m_thread(NULL)
{
    ui->setupUi(this);
    ui->btPause->setEnabled(false);
}

OpticalFlowUI::~OpticalFlowUI()
{
    delete ui;
}

void OpticalFlowUI::setOpticalFlowTools(OpticalFlowTools *optflowtools)
{
    m_optflowtools = optflowtools;
}

void OpticalFlowUI::setInputDir(const QString &inputDir)
{
     m_inputDir = inputDir;
     ui->txtInput->setText(inputDir);
}

void OpticalFlowUI::handleNewFlow(QImage *img1, QImage *img2, QImage *flow, int progress)
{
    if (img1 != NULL) { ui->lblFrame1->setPixmap(QPixmap::fromImage(*img1)); }
    if (img2 != NULL) { ui->lblFrame2->setPixmap(QPixmap::fromImage(*img2)); }
    if (flow != NULL) { ui->lblFlow->setPixmap(QPixmap::fromImage(*flow)); }
    if (progress >= 0 && progress <= 100) {
        ui->pbProgress->setValue(progress);
        ui->pbProgress->update();
    }
}

void OpticalFlowUI::on_btStart_clicked()
{

    ui->btPause->setEnabled(true);

    if (m_thread != NULL) {
        //wake it up or do nothing
        m_thread->resume();
        return;
    }

    //check folder
    if (ui->txtInput->text().isEmpty() || ui->txtOutput->text().isEmpty()) {
        qDebug() << "input or output directory";
        return;
    }

    //check compute type
    if (ui->rdGPU->isChecked()) {
        m_optflowtools->setComputationMod(OpticalFlowTools::GPU);
    } else if (ui->rdCPU->isChecked()) {
        m_optflowtools->setComputationMod(OpticalFlowTools::CPU);
    } else if (ui->rdMatlab->isChecked()) {
        m_optflowtools->setComputationMod(OpticalFlowTools::Matlab);
    }

    //fill vars
    m_inputDir = ui->txtInput->text();
    m_outputDir = ui->txtOutput->text();

    //m_optflowtools->computeFlow(img1, img2, flow);

    //ui->lblFlow->setPixmap(QPixmap::fromImage(flow));

    m_thread = new OpticalFlowThread(m_optflowtools, this);
    m_thread->setInputDir(m_inputDir);
    m_thread->setOutputDir(m_outputDir);
    connect(m_thread, &OpticalFlowThread::flowComputed, this, &OpticalFlowUI::handleNewFlow);
    m_thread->start();
}

void OpticalFlowUI::on_btClose_clicked()
{
    if(m_thread != NULL) {
        m_thread->stop();
        while(m_thread->isRunning()) { this->thread()->msleep(100);}
        delete m_thread;
    }
    this->close();
}

void OpticalFlowUI::on_btPause_clicked()
{
    if(m_thread != NULL) {
        m_thread->pause();
        ui->btPause->setEnabled(false);
    }
}
