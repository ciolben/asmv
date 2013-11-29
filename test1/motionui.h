#ifndef MOTIONUI_H
#define MOTIONUI_H

#include <QDialog>

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

private slots:
    void on_btStart_clicked();

private:
    Ui::MotionUi *ui;
    MotionThread* m_thread;

    void logText(const QString& text
                 , const QString& color = ""
                , bool bold = false
            , bool italic = false);
};

#endif // MOTIONUI_H
