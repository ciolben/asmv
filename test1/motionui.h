#ifndef MOTIONUI_H
#define MOTIONUI_H

#include <QDialog>
#include <QCloseEvent>

#include "motionthread.h"

namespace Ui {
class MotionUi;
}

class MotionUi : public QDialog
{
    Q_OBJECT

public:
    explicit MotionUi(QWidget *parent = 0);
    ~MotionUi();

    void setVideoSource(const QString& source);

signals:
    void motionProfileComputed(const QString& filename, std::vector<float> data);
    void windowClosed(const QString& identifier);

private slots:
    void on_btStart_clicked();

    virtual void closeEvent(QCloseEvent*);

private:
    Ui::MotionUi *ui;
    MotionThread* m_thread;

    void logText(const QString& text
                 , const QString& color = ""
                , bool bold = false
            , bool italic = false);
};

#endif // MOTIONUI_H
