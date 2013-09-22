#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videotools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btClose_clicked();

    void on_btOpen_clicked();

    void on_btGo_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    VideoTools vtools;

    void logText(QString text);
};

#endif // MAINWINDOW_H
