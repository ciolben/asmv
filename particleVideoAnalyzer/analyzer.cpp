#include "analyzer.h"

#include <QThread>

Analyzer::Analyzer() : public QThread
{
    Q_OBJECT

private:
//    typedef bool (MainWindow::*processNextEntry)();
//    processNextEntry m_func;
    MainWindow& m_main;
    QGraphicsView& m_view;

signals:
    void entryProcessed();

public:
    Analyzer(QGraphicsView& view, QObject* parent = 0) : QThread(parent)
      , m_main(*((MainWindow*) parent))
      , m_view(view)
    {
//        m_func = func;
    }

    void run() Q_DECL_OVERRIDE {

        while (m_main.processNextEntry()) {
            m_view.update();
            emit entryProcessed();
        };
    }
};
