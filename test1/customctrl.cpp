#include "customctrl.h"
#include "ui_customctrl.h"

CustomCtrl::CustomCtrl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomCtrl)
{
    ui->setupUi(this);
}

CustomCtrl::~CustomCtrl()
{
    delete ui;
}

void CustomCtrl::loadImages(const QString& im1, const QString& im2, const QString &out)
{
    if(im1 != 0 && !im1.isEmpty()) {
        QImage& img1 = QImage(im1);
        ui->lblIm1->setPixmap(QPixmap::fromImage(img1));
    }
    if(im2 != 0 && !im2.isEmpty()) {
        QImage& img2 = QImage(im2);
        ui->lblIm2->setPixmap(QPixmap::fromImage(img2));
    }
    if(out != 0 && !out.isEmpty()) {
        QImage& out = QImage(out);
        ui->lblFlow->setPixmap(QPixmap::fromImage(out));
    }
}

void CustomCtrl::loadImOut(const QString &out)
{
    QImage flowout = QImage(out);
    ui->lblFlow->setPixmap(QPixmap::fromImage(flowout));
}

void CustomCtrl::loadImOut(const QImage& out)
{
    if (&out != NULL) {
        ui->lblFlow->setPixmap(QPixmap::fromImage(out));
    }
}
