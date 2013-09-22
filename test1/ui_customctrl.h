/********************************************************************************
** Form generated from reading UI file 'customctrl.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMCTRL_H
#define UI_CUSTOMCTRL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomCtrl
{
public:
    QGridLayout *gridLayout;
    QRadioButton *radioButton;

    void setupUi(QWidget *CustomCtrl)
    {
        if (CustomCtrl->objectName().isEmpty())
            CustomCtrl->setObjectName(QStringLiteral("CustomCtrl"));
        CustomCtrl->resize(163, 79);
        gridLayout = new QGridLayout(CustomCtrl);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton = new QRadioButton(CustomCtrl);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 0, 0, 1, 1);


        retranslateUi(CustomCtrl);

        QMetaObject::connectSlotsByName(CustomCtrl);
    } // setupUi

    void retranslateUi(QWidget *CustomCtrl)
    {
        CustomCtrl->setWindowTitle(QApplication::translate("CustomCtrl", "Form", 0));
        radioButton->setText(QApplication::translate("CustomCtrl", "Tst Option", 0));
    } // retranslateUi

};

namespace Ui {
    class CustomCtrl: public Ui_CustomCtrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMCTRL_H
