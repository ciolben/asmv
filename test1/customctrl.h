#ifndef CUSTOMCTRL_H
#define CUSTOMCTRL_H

#include <QWidget>

namespace Ui {
class CustomCtrl;
}

class CustomCtrl : public QWidget
{
    Q_OBJECT

public:
    explicit CustomCtrl(QWidget *parent = 0);
    ~CustomCtrl();

private:
    Ui::CustomCtrl *ui;
};

#endif // CUSTOMCTRL_H
