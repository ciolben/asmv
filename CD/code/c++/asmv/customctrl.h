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

    void loadImages(const QString &im1, const QString &im2, const QString& out = 0);
    void loadImOut(const QString& out);
    void loadImOut(const QImage& out);

private:
    Ui::CustomCtrl *ui;
};

#endif // CUSTOMCTRL_H
