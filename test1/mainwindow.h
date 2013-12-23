#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "videotools.h"
#include "workerthread.h"
#include "timeline.h"

#include "opticalflowtools.h"
#include "interpolateui.h"
#include "motionui.h"

#define LEAK_DETECT 0
//**memory leak detector
#if LEAK_DETECT == 1
    #include <vld.h>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleResult(const QString *res);
    void handleNewValidFrame(qlonglong time);
    void threadFinished();
    void handleImageEaten();
    void handleTimeout();
    void handleNeedSequences(QList<Sequence *> &sequences);
    void initializeNewProfile(const QString& file, std::vector<float> profile);
    void loadMotionProfile(std::vector<float> profile, double keySimplificationFactor = 0, bool recomputeAverage = true, float ampFactor = 1.f);
    void handleWindowDestroyed(const QString& windowName);

private slots:
    void on_btClose_clicked();

    void on_btOpen_clicked();

    void on_btGo_clicked();

    void on_btFlow_clicked();

    void on_btTimeline_clicked();

    void on_slSpeed_sliderMoved(int position);

    void on_cboBuffer_currentTextChanged(const QString &arg1);

    void on_slSpeed_sliderReleased();

    void on_btInterpolate_clicked();

    void on_btMotion_clicked();

    void on_chkRemapped_clicked();

    void on_chkRemapped_stateChanged(int arg1);

    void on_sbReduction_valueChanged(double arg1);

    void on_pbResetSpline_clicked();

    void on_pbRemoveOutliers_clicked();

    void on_slOutliers_valueChanged(int value);

    void on_spTolerance_valueChanged(double arg1);

    void on_btFilter_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    VideoTools vtools;
    WorkerThread* worker;
    ImageEaterThread* imageEater;
    SplineDrawer* spline;
    OpticalFlowTools* m_optflowtools;

    InterpolateUi* m_interpUi;
    MotionUi* m_motionUi;

    QTimer timer;

    void logText(const QString *text);
    void logText(const char* text) {
        logText(&QString(text));
    }

    int dc;
    std::vector<float> m_currentProfile;
    std::vector<float> m_profile;
};

#endif // MAINWINDOW_H
