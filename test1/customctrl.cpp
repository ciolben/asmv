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
