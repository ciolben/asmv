#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "videotools.h"
#include "workerthread.h"
#include "timeline.h"

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

private slots:
    void on_btClose_clicked();

    void on_btOpen_clicked();

    void on_btGo_clicked();

    void on_btFlow_clicked();

    void on_btTimeline_clicked();

    void on_slSpeed_sliderMoved(int position);

    void on_cboBuffer_currentTextChanged(const QString &arg1);

    void on_slSpeed_sliderReleased();

private:
    Ui::MainWindow *ui;
    QString filename;
    VideoTools vtools;
    WorkerThread* worker;
    ImageEaterThread* imageEater;
    SplineDrawer* spline;

    QTimer timer;

    void logText(const QString *text);
    void logText(const char* text) {
        logText(&QString(text));
    }

    int dc;
};

#endif // MAINWINDOW_H
