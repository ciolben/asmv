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
{
    ui->setupUi(this);
}

OpticalFlowUI::~OpticalFlowUI()
{
    delete ui;
}

void OpticalFlowUI::setOpticalFlowTools(OpticalFlowTools *optflowtools)
{
    m_optflowtools = optflowtools;
}

void OpticalFlowUI::handleNewFlow(QImage *img1, QImage *img2, QImage *flow)
{
    if (img1 != NULL) { ui->lblFrame1->setPixmap(QPixmap::fromImage(*img1)); }
    if (img2 != NULL) { ui->lblFrame2->setPixmap(QPixmap::fromImage(*img2)); }
    if (flow != NULL) { ui->lblFlow->setPixmap(QPixmap::fromImage(*flow)); }
}

void OpticalFlowUI::on_btStart_clicked()
{

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

    //test
//    QImage* img1 = new QImage("car1.jpg");
//    QImage* img2 = new QImage("car2.jpg");
//    QImage* flow;
//    ui->lblFrame1->setPixmap(QPixmap::fromImage(*img1));
//    ui->lblFrame2->setPixmap(QPixmap::fromImage(*img2));

    //m_optflowtools->computeFlow(img1, img2, flow);

    //ui->lblFlow->setPixmap(QPixmap::fromImage(flow));

    m_thread = new OpticalFlowThread(m_optflowtools, this);
    m_thread->setInputDir(m_inputDir);
    m_thread->setOutputDir(m_outputDir);
    connect(m_thread, &OpticalFlowThread::flowComputed, this, &OpticalFlowUI::handleNewFlow);
    m_thread->start();
}
