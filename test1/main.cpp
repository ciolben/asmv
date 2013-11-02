#include "mainwindow.h"
#include <QApplication>

//#include "opticalflow/opencv/optical_flow.cpp"

int main(int argc, char *argv[])
{
//    char** argv2 = new char*[2];
//    argv2[0] = "car1.jpg"; argv2[1] = "car2.jpg";
//    start(argv2[0], argv2[1]);
//    return 0;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
