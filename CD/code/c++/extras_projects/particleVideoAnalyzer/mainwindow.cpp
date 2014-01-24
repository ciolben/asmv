#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>

#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_tproc(TextProcessing())
  , m_scene(this)
  , m_maxWidth(0)
  , m_maxHeight(0)
  , m_maxparticle(0)
  , m_count(0)
  , m_pix(NULL)
  , m_analyzers(QList<process>())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    m_maxWidth = ui->graphicsView->width();
    m_maxHeight = ui->graphicsView->height();

    int number = m_tproc.setContent("C:/Users/Loic/Coding_Main/ADM/pvl/VCars-pv.txt");
    ui->statusBar->showMessage(QString("File : %1 | Number of particles : %2").arg("VCars-pv.txt").arg(number));
    m_maxparticle  = number;

    ui->pbAnalyze->setMaximum(number);
    ui->pbAnalyze->setMinimum(0);
    ui->pbAnalyze->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleEntryProcessed()
{
    m_count++;
    ui->pbAnalyze->setValue(m_count);
//    if (m_count % 1000 == 0) {
//        QCoreApplication::processEvents(); //very slow
//    }
}

void MainWindow::handleNeedResize(int width, int height)
{
    bool hasChanged = false;
    if (width > m_maxWidth) {
        m_maxWidth = width;
        hasChanged = true;
    }
    if (height > m_maxHeight) {
        m_maxHeight = height;
        hasChanged = true;
    }

    if (hasChanged) {
//        ui->graphicsView->fitInView(m_scene.sceneRect());
//        update();
    }
}

void MainWindow::handleAnalyzeFinished()
{
    m_tproc.resetToBegining();
    m_count = 0;
    ui->statusBar->showMessage(QString("Analyze finished"));
}

void MainWindow::on_actionOpen_triggered()
{
    QString res = QFileDialog::getOpenFileName(this, "Open sps file", QDir::homePath());
    if (res.isEmpty()) { return; }
    QFile file(res);
    if (!file.exists()) { return;  }

    if (m_tproc.isSet()) {
       /* don */
    }
    int number = m_tproc.setContent(res);
    ui->statusBar->showMessage(QString("File : %1 | Number of particles : %2").arg(file.fileName()).arg(number));
    if (number == -1) {
        return;
    }
    ui->pbAnalyze->setMaximum(number);
    m_maxparticle = number;
}

void MainWindow::on_actionStart_triggered()
{
    if (m_analyzers.size() == 0) {
        addAnalyzer();
    }
    process proc = m_analyzers.at(0);
    proc.first->processNextEntry();
}

void MainWindow::on_actionClear_triggered()
{
    m_scene.clear();
    m_tproc.resetToBegining();
}

void MainWindow::on_actionStart_2_triggered()
{
    startAnayzing(Analyzer::Draw);
}

void MainWindow::on_actionDump_to_Matlab_format_triggered()
{
    startAnayzing(Analyzer::ToFile);
}

void MainWindow::addAnalyzer()
{
    QThread* thread = new QThread();
    Analyzer* a = new Analyzer(&m_tproc, &m_scene, this);
    m_analyzers.append(process(a, thread));
    connect(a, &Analyzer::entryProcessed, this, &MainWindow::handleEntryProcessed);
    connect(a, &Analyzer::needResize, this, &MainWindow::handleNeedResize);
    connect(a, &Analyzer::finished, this, &MainWindow::handleAnalyzeFinished);
    a->moveToThread(thread);
}

void MainWindow::startAnayzing(Analyzer::AnalyzeMod mod)
{
    //start a new worker
    if (m_count > 0) { return; }

    //TODO : check nb cpu
    if (m_analyzers.size() == 0) {
        addAnalyzer();
    }
    foreach(process proc, m_analyzers) {
        Analyzer* analyzer = proc.first;
        QThread* thread = proc.second;
        thread->start();
        analyzer->setMod(mod);
        analyzer->analyze();
    }
}
