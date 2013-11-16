#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "textprocessing.h"

#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool processNextEntry();

public slots:
    void handleEnryProcessed();

private slots:
    void on_actionOpen_triggered();

    void on_actionStart_triggered();

    void on_actionClear_triggered();

    void on_actionStart_2_triggered();

private:
    Ui::MainWindow *ui;
    TextProcessing m_tproc;

    QGraphicsScene m_scene;
    int m_maxx, m_maxy;
    int m_maxparticle;
    int m_count;

};

#endif // MAINWINDOW_H
