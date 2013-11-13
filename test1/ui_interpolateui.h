/********************************************************************************
** Form generated from reading UI file 'interpolateui.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERPOLATEUI_H
#define UI_INTERPOLATEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InterpolateUi
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *txtRate;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_3;
    QPushButton *btLoad;
    QLineEdit *txtSrc;
    QPushButton *btInterpolate;
    QLineEdit *txtOut;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QProgressBar *pbProgress;

    void setupUi(QDialog *InterpolateUi)
    {
        if (InterpolateUi->objectName().isEmpty())
            InterpolateUi->setObjectName(QStringLiteral("InterpolateUi"));
        InterpolateUi->resize(400, 199);
        gridLayout = new QGridLayout(InterpolateUi);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(InterpolateUi);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 3, 1, 1);

        txtRate = new QLineEdit(groupBox);
        txtRate->setObjectName(QStringLiteral("txtRate"));

        gridLayout_2->addWidget(txtRate, 0, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        btLoad = new QPushButton(groupBox);
        btLoad->setObjectName(QStringLiteral("btLoad"));

        gridLayout_2->addWidget(btLoad, 4, 0, 1, 1);

        txtSrc = new QLineEdit(groupBox);
        txtSrc->setObjectName(QStringLiteral("txtSrc"));

        gridLayout_2->addWidget(txtSrc, 2, 2, 1, 1);

        btInterpolate = new QPushButton(groupBox);
        btInterpolate->setObjectName(QStringLiteral("btInterpolate"));

        gridLayout_2->addWidget(btInterpolate, 4, 2, 1, 1);

        txtOut = new QLineEdit(groupBox);
        txtOut->setObjectName(QStringLiteral("txtOut"));

        gridLayout_2->addWidget(txtOut, 3, 2, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(InterpolateUi);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbProgress = new QProgressBar(groupBox_2);
        pbProgress->setObjectName(QStringLiteral("pbProgress"));
        pbProgress->setMinimum(5);
        pbProgress->setTextVisible(true);

        horizontalLayout->addWidget(pbProgress);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(InterpolateUi);

        QMetaObject::connectSlotsByName(InterpolateUi);
    } // setupUi

    void retranslateUi(QDialog *InterpolateUi)
    {
        InterpolateUi->setWindowTitle(QApplication::translate("InterpolateUi", "Dialog", 0));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("InterpolateUi", "ms", 0));
        txtRate->setText(QApplication::translate("InterpolateUi", "40", 0));
        label->setText(QApplication::translate("InterpolateUi", "Rate :", 0));
        label_4->setText(QApplication::translate("InterpolateUi", "Output dir :", 0));
        label_3->setText(QApplication::translate("InterpolateUi", "Source dir :", 0));
        btLoad->setText(QApplication::translate("InterpolateUi", "Load sequences", 0));
        txtSrc->setText(QApplication::translate("InterpolateUi", "out/", 0));
        btInterpolate->setText(QApplication::translate("InterpolateUi", "Interpolate", 0));
        txtOut->setText(QApplication::translate("InterpolateUi", "interpolated/", 0));
        groupBox_2->setTitle(QApplication::translate("InterpolateUi", "Progression", 0));
    } // retranslateUi

};

namespace Ui {
    class InterpolateUi: public Ui_InterpolateUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERPOLATEUI_H
