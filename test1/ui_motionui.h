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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
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
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *txtMaxDist;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtMinClustSize;
    QLineEdit *txtMinValue;
    QLabel *label_9;
    QCheckBox *chkWriteMotion;
    QRadioButton *rdWflow;
    QRadioButton *rdAfflow;
    QRadioButton *rdBoth;
    QSlider *slSmooth;
    QLabel *label_10;
    QLabel *lblSmooth;
    QLabel *label_11;
    QSpinBox *sbReduction;
    QLabel *label_12;

    void setupUi(QDialog *MotionUi)
    {
        if (MotionUi->objectName().isEmpty())
            MotionUi->setObjectName(QStringLiteral("MotionUi"));
        MotionUi->resize(384, 440);
        label = new QLabel(MotionUi);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 16));
        txtSource = new QLineEdit(MotionUi);
        txtSource->setObjectName(QStringLiteral("txtSource"));
        txtSource->setGeometry(QRect(90, 10, 271, 20));
        txtOut = new QTextEdit(MotionUi);
        txtOut->setObjectName(QStringLiteral("txtOut"));
        txtOut->setGeometry(QRect(10, 210, 351, 181));
        txtOut->setReadOnly(true);
        label_2 = new QLabel(MotionUi);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 180, 46, 13));
        btStart = new QPushButton(MotionUi);
        btStart->setObjectName(QStringLiteral("btStart"));
        btStart->setGeometry(QRect(290, 410, 75, 23));
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
        label_4 = new QLabel(MotionUi);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 46, 20));
        label_5 = new QLabel(MotionUi);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 70, 51, 21));
        label_6 = new QLabel(MotionUi);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 70, 46, 21));
        txtMaxDist = new QLineEdit(MotionUi);
        txtMaxDist->setObjectName(QStringLiteral("txtMaxDist"));
        txtMaxDist->setGeometry(QRect(120, 70, 41, 20));
        label_7 = new QLabel(MotionUi);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(170, 70, 71, 20));
        label_8 = new QLabel(MotionUi);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(280, 70, 31, 21));
        txtMinClustSize = new QLineEdit(MotionUi);
        txtMinClustSize->setObjectName(QStringLiteral("txtMinClustSize"));
        txtMinClustSize->setGeometry(QRect(240, 70, 31, 20));
        txtMinValue = new QLineEdit(MotionUi);
        txtMinValue->setObjectName(QStringLiteral("txtMinValue"));
        txtMinValue->setGeometry(QRect(310, 70, 31, 20));
        label_9 = new QLabel(MotionUi);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 130, 46, 13));
        chkWriteMotion = new QCheckBox(MotionUi);
        chkWriteMotion->setObjectName(QStringLiteral("chkWriteMotion"));
        chkWriteMotion->setGeometry(QRect(70, 130, 111, 17));
        chkWriteMotion->setChecked(true);
        rdWflow = new QRadioButton(MotionUi);
        rdWflow->setObjectName(QStringLiteral("rdWflow"));
        rdWflow->setGeometry(QRect(190, 130, 51, 17));
        rdWflow->setChecked(true);
        rdAfflow = new QRadioButton(MotionUi);
        rdAfflow->setObjectName(QStringLiteral("rdAfflow"));
        rdAfflow->setGeometry(QRect(250, 130, 51, 17));
        rdBoth = new QRadioButton(MotionUi);
        rdBoth->setObjectName(QStringLiteral("rdBoth"));
        rdBoth->setGeometry(QRect(310, 130, 82, 17));
        slSmooth = new QSlider(MotionUi);
        slSmooth->setObjectName(QStringLiteral("slSmooth"));
        slSmooth->setGeometry(QRect(149, 100, 141, 20));
        slSmooth->setMaximum(100);
        slSmooth->setValue(24);
        slSmooth->setOrientation(Qt::Horizontal);
        label_10 = new QLabel(MotionUi);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(70, 100, 61, 16));
        lblSmooth = new QLabel(MotionUi);
        lblSmooth->setObjectName(QStringLiteral("lblSmooth"));
        lblSmooth->setGeometry(QRect(300, 100, 21, 16));
        label_11 = new QLabel(MotionUi);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(320, 100, 41, 16));
        sbReduction = new QSpinBox(MotionUi);
        sbReduction->setObjectName(QStringLiteral("sbReduction"));
        sbReduction->setGeometry(QRect(150, 150, 42, 21));
        sbReduction->setMaximum(100);
        sbReduction->setValue(2);
        label_12 = new QLabel(MotionUi);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(70, 150, 81, 20));

        retranslateUi(MotionUi);
        QObject::connect(slSmooth, SIGNAL(valueChanged(int)), lblSmooth, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(MotionUi);
    } // setupUi

    void retranslateUi(QDialog *MotionUi)
    {
        MotionUi->setWindowTitle(QApplication::translate("MotionUi", "SceneMotion", 0));
        label->setText(QApplication::translate("MotionUi", "Video source :", 0));
        label_2->setText(QApplication::translate("MotionUi", "Output :", 0));
        btStart->setText(QApplication::translate("MotionUi", "Start", 0));
        label_3->setText(QApplication::translate("MotionUi", "Steps :", 0));
        chkAffine->setText(QApplication::translate("MotionUi", "1. Affine", 0));
        chkwflow->setText(QApplication::translate("MotionUi", "2. w-flow", 0));
        chkProfiling->setText(QApplication::translate("MotionUi", "3. Motion Estimation", 0));
        label_4->setText(QApplication::translate("MotionUi", "Spline :", 0));
        label_5->setText(QApplication::translate("MotionUi", "Clusters :", 0));
        label_6->setText(QApplication::translate("MotionUi", "MaxDist :", 0));
        txtMaxDist->setText(QApplication::translate("MotionUi", "0.5", 0));
        label_7->setText(QApplication::translate("MotionUi", "MinClustSize :", 0));
        label_8->setText(QApplication::translate("MotionUi", "Bkg : ", 0));
        txtMinClustSize->setText(QApplication::translate("MotionUi", "10", 0));
        txtMinValue->setText(QApplication::translate("MotionUi", "0.5", 0));
        label_9->setText(QApplication::translate("MotionUi", "Others :", 0));
        chkWriteMotion->setText(QApplication::translate("MotionUi", "Write motion.clust", 0));
        rdWflow->setText(QApplication::translate("MotionUi", "wflow", 0));
        rdAfflow->setText(QApplication::translate("MotionUi", "afflow", 0));
        rdBoth->setText(QApplication::translate("MotionUi", "both", 0));
        label_10->setText(QApplication::translate("MotionUi", "Smoothing :", 0));
        lblSmooth->setText(QApplication::translate("MotionUi", "24", 0));
        label_11->setText(QApplication::translate("MotionUi", "frames", 0));
        label_12->setText(QApplication::translate("MotionUi", "Reduce keys by ", 0));
    } // retranslateUi

};

namespace Ui {
    class MotionUi: public Ui_MotionUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOTIONUI_H
