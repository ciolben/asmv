#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_btTest_clicked();

private:
    Ui::MainWindow *ui;
    void logText(QString text);
    void logText(int text);
    void printArray(const float* a, const unsigned int n);
};

#endif // MAINWINDOW_H
