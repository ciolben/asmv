#include "addsequencedialog.h"
#include "ui_addsequencedialog.h"

AddSequenceDialog::AddSequenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSequenceDialog)
{
    ui->setupUi(this);
}

AddSequenceDialog::~AddSequenceDialog()
{
    delete ui;
}
