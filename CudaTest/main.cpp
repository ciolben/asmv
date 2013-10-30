#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication aq(argc, argv);
    MainWindow w;
    w.show();



    return aq.exec();
}
