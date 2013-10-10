#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videotools.h"

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

private slots:
    void on_btClose_clicked();

    void on_btOpen_clicked();

    void on_btGo_clicked();

    void on_btClean_clicked();

    void on_btFlow_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    VideoTools vtools;

    void logText(const QString *text);
    void logText(const char* text) {
        logText(&QString(text));
    }

    int dc;
};

#endif // MAINWINDOW_H
