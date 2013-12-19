#ifndef OPTICALFLOWUI_H
#define OPTICALFLOWUI_H

#include <QDialog>

#include "opticalflowtools.h"
#include "opticalflowthread.h"

namespace Ui {
class OpticalFlowUI;
}

class OpticalFlowUI : public QDialog
{
    Q_OBJECT

public:
    explicit OpticalFlowUI(QWidget *parent = 0);
    ~OpticalFlowUI();

    void setOpticalFlowTools(OpticalFlowTools* optflowtools);

    QString getOutputDir() const { return m_outputDir; }
    void setOutputDir(const QString &outputDir) { m_outputDir = outputDir;}
    QString getInputDir() const { return m_inputDir; }
    void setInputDir(const QString &inputDir);

public slots:
    void handleNewFlow(QImage* img1, QImage* img2, QImage* flow, int progress);

private slots:
    void on_btStart_clicked();

    void on_btClose_clicked();

    void on_btPause_clicked();

private:
    Ui::OpticalFlowUI *ui;
    QString m_inputDir;
    QString m_outputDir;

    OpticalFlowTools* m_optflowtools;
    OpticalFlowThread* m_thread;

    void computeOpticalFlow();


};

#endif // OPTICALFLOWUI_H
