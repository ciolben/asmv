#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qmediaplayer.h>
#include <QMainWindow>
#include <QtGui/QMovie>
#include <QtWidgets/QWidget>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
//    QMediaPlayer player;
};

#endif // MAINWINDOW_H
