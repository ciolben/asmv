#include "mainwindow.h"
#include <QApplication>

//#include "opticalflow/opencv/optical_flow.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
