#ifndef INTERPOLATEUI_H
#define INTERPOLATEUI_H

#include <QDialog>

#include "timelineQML/Sequence.hpp"
#include "opticalflowtools.h"

namespace Ui {
class InterpolateUi;
}

class InterpolateUi : public QDialog
{
    Q_OBJECT

public:
    explicit InterpolateUi(QWidget *parent = 0);
    ~InterpolateUi();

private slots:
    void on_btInterpolate_clicked();

    void on_btLoad_clicked();

signals:
    //want to load sequences
    void needSequences(QList<Sequence*>& sequences);

private:
    Ui::InterpolateUi *ui;
    QList<Sequence*> m_sequences;
    OpticalFlowTools m_optflowtools;

};

#endif // INTERPOLATEUI_H
