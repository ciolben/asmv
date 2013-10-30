#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cuda.h>
#include <builtin_types.h>
#include "drvapi_error_string.h"

#include <QDebug>

// Forward declare the function in the .cu file
void vectorAddition(const float* a, const float* b, float* c, int n);

void MainWindow::printArray(const float* a, const unsigned int n) {
    QString s = "(";
    unsigned int ii;
    for (ii = 0; ii < n - 1; ++ii)
        s.append(QString::number(a[ii])).append(", ");
    s.append(QString::number(a[ii])).append(")");

    logText(s);
}

void MainWindow::logText(QString text) {
    QString result = ui->txtOut->toPlainText();
    ui->txtOut->setPlainText(result.append(text.append("\n")));
}

void MainWindow::logText(int text) {
    logText(QString("%1").arg(text));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btTest_clicked()
{
    int deviceCount = 0;
    int cudaDevice = 0;
    char cudaDeviceName [100];

    unsigned int N = 50;
    float *a, *b, *c;

    cuInit(0);
    cuDeviceGetCount(&deviceCount);
    cuDeviceGet(&cudaDevice, 0);
    cuDeviceGetName(cudaDeviceName, 100, cudaDevice);
    logText("Number of devices: "); logText(deviceCount);
    logText("Device name:"); logText(cudaDeviceName);

    a = new float [N];    b = new float [N];    c = new float [N];
    for (unsigned int ii = 0; ii < N; ++ii) {
        a[ii] = qrand();
        b[ii] = qrand();
    }

    // This is the function call in which the kernel is called
    vectorAddition(a, b, c, N);

    logText("input a:"); printArray(a, N);
    logText("input b:"); printArray(b, N);
    logText("output c:"); printArray(c, N);

    if (a) delete a;
    if (b) delete b;
    if (c) delete c;
}
