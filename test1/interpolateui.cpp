#include "interpolateui.h"
#include "ui_interpolateui.h"

#include <QDir>

#include <QDebug>

InterpolateUi::InterpolateUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterpolateUi)
    , m_sequences(QList<Sequence*>())
    , m_optflowtools(OpticalFlowTools())
{
    ui->setupUi(this);
}

InterpolateUi::~InterpolateUi()
{
    delete ui;
}

void InterpolateUi::on_btInterpolate_clicked()
{
    if (m_sequences.isEmpty()) { return; }
    QString strOutdir = ui->txtOut->text();
    if (strOutdir.isEmpty()) { return; }
    QString strSrcdir = ui->txtSrc->text();
    if (strSrcdir.isEmpty()) { return; }
    int rate = 0;
    try { rate = ui->txtRate->text().toInt();
    } catch (...) { return; }

    QDir srcdir(strSrcdir);
    QStringList filters; filters << "*.png" << "*.jpg" << "*.jpeg";
    QFileInfoList files = srcdir.entryInfoList(filters
                                             , QDir::Files
                                             , QDir::Name);

    foreach (QFileInfo file, files) {
        qDebug() << file.baseName();
    }

}

void InterpolateUi::on_btLoad_clicked()
{
    m_sequences.clear();
    emit needSequences(m_sequences);
}
