#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "textprocessing.h"

#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "analyzer.h"

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
    void handleEntryProcessed();
    void handleNeedResize(int width, int height);
    void handleAnalyzeFinished();

private slots:
    void on_actionOpen_triggered();

    void on_actionStart_triggered();

    void on_actionClear_triggered();

    void on_actionStart_2_triggered();

    void on_actionDump_to_Matlab_format_triggered();

private:
    Ui::MainWindow *ui;
    TextProcessing m_tproc;

    QGraphicsScene m_scene;
    QGraphicsPixmapItem* m_pix;
    int m_maxWidth, m_maxHeight;
    int m_maxparticle;
    int m_count;

    typedef std::pair<Analyzer*, QThread*> process;
    QList<process> m_analyzers;

    void addAnalyzer();
    void startAnayzing(Analyzer::AnalyzeMod mod);
};

#endif // MAINWINDOW_H
