/********************************************************************************
** Form generated from reading UI file 'motionui.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOTIONUI_H
#define UI_MOTIONUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_MotionUi
{
public:
    QLabel *label;
    QLineEdit *txtSource;
    QTextEdit *txtOut;
    QLabel *label_2;
    QPushButton *btStart;
    QLabel *label_3;
    QSplitter *splitter;
    QCheckBox *chkAffine;
    QCheckBox *chkwflow;
    QCheckBox *chkProfiling;

    void setupUi(QDialog *MotionUi)
    {
        if (MotionUi->objectName().isEmpty())
            MotionUi->setObjectName(QStringLiteral("MotionUi"));
        MotionUi->resize(384, 365);
        label = new QLabel(MotionUi);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 16));
        txtSource = new QLineEdit(MotionUi);
        txtSource->setObjectName(QStringLiteral("txtSource"));
        txtSource->setGeometry(QRect(90, 10, 271, 20));
        txtOut = new QTextEdit(MotionUi);
        txtOut->setObjectName(QStringLiteral("txtOut"));
        txtOut->setGeometry(QRect(10, 110, 351, 201));
        txtOut->setReadOnly(true);
        label_2 = new QLabel(MotionUi);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 46, 13));
        btStart = new QPushButton(MotionUi);
        btStart->setObjectName(QStringLiteral("btStart"));
        btStart->setGeometry(QRect(290, 330, 75, 23));
        label_3 = new QLabel(MotionUi);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 50, 46, 13));
        splitter = new QSplitter(MotionUi);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(70, 50, 271, 17));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(10);
        chkAffine = new QCheckBox(splitter);
        chkAffine->setObjectName(QStringLiteral("chkAffine"));
        splitter->addWidget(chkAffine);
        chkwflow = new QCheckBox(splitter);
        chkwflow->setObjectName(QStringLiteral("chkwflow"));
        splitter->addWidget(chkwflow);
        chkProfiling = new QCheckBox(splitter);
        chkProfiling->setObjectName(QStringLiteral("chkProfiling"));
        chkProfiling->setChecked(true);
        splitter->addWidget(chkProfiling);

        retranslateUi(MotionUi);

        QMetaObject::connectSlotsByName(MotionUi);
    } // setupUi

    void retranslateUi(QDialog *MotionUi)
    {
        MotionUi->setWindowTitle(QApplication::translate("MotionUi", "Dialog", 0));
        label->setText(QApplication::translate("MotionUi", "Video source :", 0));
        label_2->setText(QApplication::translate("MotionUi", "Output :", 0));
        btStart->setText(QApplication::translate("MotionUi", "Start", 0));
        label_3->setText(QApplication::translate("MotionUi", "Steps :", 0));
        chkAffine->setText(QApplication::translate("MotionUi", "1. Affine", 0));
        chkwflow->setText(QApplication::translate("MotionUi", "2. w-flow", 0));
        chkProfiling->setText(QApplication::translate("MotionUi", "3. Motion Estimation", 0));
    } // retranslateUi

};

namespace Ui {
    class MotionUi: public Ui_MotionUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTIONUI_H
