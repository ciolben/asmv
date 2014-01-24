#ifndef INTERPOLATEUI_H
#define INTERPOLATEUI_H

#include <QDialog>
#include <QCloseEvent>

#include "timelineQML/splinedrawer.h"
#include "timelineQML/Sequence.hpp"
#include "opticalflowtools.h"

namespace Ui {
class InterpolateUi;
}

class InterpolateUi : public QDialog
{
    Q_OBJECT

public:
    explicit InterpolateUi(SplineDrawer *spline, QWidget *parent = 0);
    ~InterpolateUi();

    void addBaseName(const QString& basename);
    void setTpf(const QString& tpf);

private slots:
    void on_btInterpolate_clicked();

    virtual void closeEvent(QCloseEvent*);

signals:
    //want to load sequences
    void needSequences(QList<Sequence*>& sequences);
    void windowClosed(const QString& identifier);

private:
    Ui::InterpolateUi *ui;
    QList<Sequence*> m_sequences;
    SplineDrawer* m_spline;
    OpticalFlowTools m_optflowtools;

};

#endif // INTERPOLATEUI_H
