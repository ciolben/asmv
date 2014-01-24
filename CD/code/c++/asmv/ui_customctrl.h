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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomCtrl
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_3;
    QLabel *lblIm1;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QLabel *lblFlow;
    QGroupBox *groupBox_2;
    QLabel *lblIm2;

    void setupUi(QWidget *CustomCtrl)
    {
        if (CustomCtrl->objectName().isEmpty())
            CustomCtrl->setObjectName(QStringLiteral("CustomCtrl"));
        CustomCtrl->resize(716, 205);
        CustomCtrl->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout_2 = new QHBoxLayout(CustomCtrl);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_3 = new QGroupBox(CustomCtrl);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        lblIm1 = new QLabel(groupBox_3);
        lblIm1->setObjectName(QStringLiteral("lblIm1"));
        lblIm1->setGeometry(QRect(10, 20, 211, 161));
        lblIm1->setFrameShape(QFrame::Box);

        horizontalLayout_2->addWidget(groupBox_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(CustomCtrl);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        lblFlow = new QLabel(groupBox);
        lblFlow->setObjectName(QStringLiteral("lblFlow"));
        lblFlow->setGeometry(QRect(10, 20, 211, 161));
        lblFlow->setFrameShape(QFrame::Box);
        lblFlow->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(groupBox);


        horizontalLayout_2->addLayout(horizontalLayout);

        groupBox_2 = new QGroupBox(CustomCtrl);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        lblIm2 = new QLabel(groupBox_2);
        lblIm2->setObjectName(QStringLiteral("lblIm2"));
        lblIm2->setGeometry(QRect(10, 20, 211, 161));
        lblIm2->setFrameShape(QFrame::Box);
        lblIm2->setFrameShadow(QFrame::Plain);

        horizontalLayout_2->addWidget(groupBox_2);


        retranslateUi(CustomCtrl);

        QMetaObject::connectSlotsByName(CustomCtrl);
    } // setupUi

    void retranslateUi(QWidget *CustomCtrl)
    {
        CustomCtrl->setWindowTitle(QApplication::translate("CustomCtrl", "Form", 0));
        groupBox_3->setTitle(QApplication::translate("CustomCtrl", "Image 1", 0));
        lblIm1->setText(QString());
        groupBox->setTitle(QApplication::translate("CustomCtrl", "Flow", 0));
        lblFlow->setText(QString());
        groupBox_2->setTitle(QApplication::translate("CustomCtrl", "Image 2", 0));
        lblIm2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CustomCtrl: public Ui_CustomCtrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMCTRL_H
