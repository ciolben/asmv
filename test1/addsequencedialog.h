#ifndef ADDSEQUENCEDIALOG_H
#define ADDSEQUENCEDIALOG_H

#include <QDialog>

namespace Ui {
class AddSequenceDialog;
}

class AddSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSequenceDialog(QWidget *parent = 0);
    ~AddSequenceDialog();

private:
    Ui::AddSequenceDialog *ui;
};

#endif // ADDSEQUENCEDIALOG_H
