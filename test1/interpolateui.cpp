#include "interpolateui.h"
#include "ui_interpolateui.h"

#include <QDir>

#include <QDebug>

InterpolateUi::InterpolateUi(SplineDrawer* spline, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterpolateUi)
    , m_sequences(QList<Sequence*>())
    , m_spline(spline)
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
    ui->btInterpolate->setEnabled(false);

    //load sequences profile
    m_sequences.clear();

    //direct
    emit needSequences(m_sequences);

    //check dirs
    QString strOutdir = ui->txtOut->text();
    if (strOutdir.isEmpty()) { return; }
    QString strSrcdir = ui->txtSrc->text();
    if (strSrcdir.isEmpty()) { return; }
    int tps = 0;
    try { tps = ui->txtRate->text().toInt();
    } catch (...) { return; }


    QDir srcdir(strSrcdir);
    QStringList filterImg; filterImg << "*.png" << "*.jpg" << "*.jpeg";
    QStringList filterFlow; filterFlow << "*.gz";
    QFileInfoList images = srcdir.entryInfoList(filterImg
                                             , QDir::Files
                                             , QDir::Name);
    QFileInfoList flows = srcdir.entryInfoList(filterFlow
                                                 , QDir::Files
                                                 , QDir::Name);

    QDir destdir("./");
    destdir.mkdir(strOutdir);
    destdir.cd(strOutdir);

    auto sortfun = []
            (const QFileInfo f1, const QFileInfo f2) -> bool {
                int l1 = f1.baseName().length();
                int l2 = f2.baseName().length();
                if (l1 < l2) { return true; }
                if (l2 < l1) { return false; }
                return f1.baseName().compare(f2.baseName()) < 0;
            };

    qSort(images.begin(), images.end(), sortfun);
    qSort(flows.begin(), flows.end(), sortfun);

    ulong currentTime = 0;
    for (int i = 0; i < images.size() - 1; ++i) {
        //extract frame number from filename
        const QFileInfo qfile1 = images.at(i);
        const QFileInfo qfile2 = images.at(i + 1);
        const QFileInfo flow12 = flows.at(i);
        int frameNumber;
        sscanf(qfile1.baseName().toLocal8Bit().constData(), "img%d", &frameNumber);

        //get interpolation factor
        QList<float> ratios = m_spline->getInterpolationFactors(tps, currentTime);
        currentTime += tps;

        QString dbg("ratios");
        foreach (float f, ratios) {
            dbg += " : " + QString::number(f);
        }
        qDebug() << dbg;
    }

    ui->btInterpolate->setEnabled(true);
}

void InterpolateUi::closeEvent(QCloseEvent*)
{
    emit windowClosed("interpolation");
}

void InterpolateUi::on_btOpticalFlow_clicked()
{

}
