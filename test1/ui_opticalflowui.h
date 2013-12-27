/********************************************************************************
** Form generated from reading UI file 'opticalflowui.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTICALFLOWUI_H
#define UI_OPTICALFLOWUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OpticalFlowUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rdGPU;
    QRadioButton *rdCPU;
    QRadioButton *rdMatlab;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblFrame1;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblFlow;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblFrame2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QProgressBar *pbProgress;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *txtInput;
    QLabel *label_7;
    QLineEdit *txtOutput;
    QPushButton *btStart;
    QPushButton *btPause;
    QPushButton *btClose;

    void setupUi(QDialog *OpticalFlowUI)
    {
        if (OpticalFlowUI->objectName().isEmpty())
            OpticalFlowUI->setObjectName(QStringLiteral("OpticalFlowUI"));
        OpticalFlowUI->resize(614, 516);
        verticalLayout = new QVBoxLayout(OpticalFlowUI);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(OpticalFlowUI);
        label->setObjectName(QStringLiteral("label"));
        QPalette palette;
        QBrush brush(QColor(133, 173, 38, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        QBrush brush4(QColor(56, 199, 12, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush5);
        label->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        groupBox = new QGroupBox(OpticalFlowUI);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rdGPU = new QRadioButton(groupBox);
        rdGPU->setObjectName(QStringLiteral("rdGPU"));
        rdGPU->setChecked(true);

        horizontalLayout->addWidget(rdGPU);

        rdCPU = new QRadioButton(groupBox);
        rdCPU->setObjectName(QStringLiteral("rdCPU"));
        rdCPU->setChecked(false);

        horizontalLayout->addWidget(rdCPU);

        rdMatlab = new QRadioButton(groupBox);
        rdMatlab->setObjectName(QStringLiteral("rdMatlab"));

        horizontalLayout->addWidget(rdMatlab);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(OpticalFlowUI);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lblFrame1 = new QLabel(groupBox_5);
        lblFrame1->setObjectName(QStringLiteral("lblFrame1"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblFrame1->sizePolicy().hasHeightForWidth());
        lblFrame1->setSizePolicy(sizePolicy);
        lblFrame1->setMinimumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(lblFrame1);


        horizontalLayout_2->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblFlow = new QLabel(groupBox_6);
        lblFlow->setObjectName(QStringLiteral("lblFlow"));
        sizePolicy.setHeightForWidth(lblFlow->sizePolicy().hasHeightForWidth());
        lblFlow->setSizePolicy(sizePolicy);
        lblFlow->setMinimumSize(QSize(100, 100));

        horizontalLayout_4->addWidget(lblFlow);


        horizontalLayout_2->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_7);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lblFrame2 = new QLabel(groupBox_7);
        lblFrame2->setObjectName(QStringLiteral("lblFrame2"));
        sizePolicy.setHeightForWidth(lblFrame2->sizePolicy().hasHeightForWidth());
        lblFrame2->setSizePolicy(sizePolicy);
        lblFrame2->setMinimumSize(QSize(100, 100));

        horizontalLayout_5->addWidget(lblFrame2);


        horizontalLayout_2->addWidget(groupBox_7);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(OpticalFlowUI);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pbProgress = new QProgressBar(groupBox_3);
        pbProgress->setObjectName(QStringLiteral("pbProgress"));
        pbProgress->setValue(0);

        horizontalLayout_6->addWidget(pbProgress);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(OpticalFlowUI);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_4);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_7->addWidget(label_6);

        txtInput = new QLineEdit(groupBox_4);
        txtInput->setObjectName(QStringLiteral("txtInput"));

        horizontalLayout_7->addWidget(txtInput);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        txtOutput = new QLineEdit(groupBox_4);
        txtOutput->setObjectName(QStringLiteral("txtOutput"));
        txtOutput->setEnabled(false);

        horizontalLayout_7->addWidget(txtOutput);

        btStart = new QPushButton(groupBox_4);
        btStart->setObjectName(QStringLiteral("btStart"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btStart->setIcon(icon);

        horizontalLayout_7->addWidget(btStart);

        btPause = new QPushButton(groupBox_4);
        btPause->setObjectName(QStringLiteral("btPause"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btPause->setIcon(icon1);

        horizontalLayout_7->addWidget(btPause);

        btClose = new QPushButton(groupBox_4);
        btClose->setObjectName(QStringLiteral("btClose"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btClose->setIcon(icon2);

        horizontalLayout_7->addWidget(btClose);


        verticalLayout->addWidget(groupBox_4);


        retranslateUi(OpticalFlowUI);

        QMetaObject::connectSlotsByName(OpticalFlowUI);
    } // setupUi

    void retranslateUi(QDialog *OpticalFlowUI)
    {
        OpticalFlowUI->setWindowTitle(QApplication::translate("OpticalFlowUI", "Compute Optical Flow", 0));
        label->setText(QApplication::translate("OpticalFlowUI", "Optical Flow", 0));
        groupBox->setTitle(QApplication::translate("OpticalFlowUI", "Computation", 0));
        rdGPU->setText(QApplication::translate("OpticalFlowUI", "GPU", 0));
        rdCPU->setText(QApplication::translate("OpticalFlowUI", "CPU", 0));
        rdMatlab->setText(QApplication::translate("OpticalFlowUI", "Matlab", 0));
        groupBox_2->setTitle(QApplication::translate("OpticalFlowUI", "Images", 0));
        groupBox_5->setTitle(QApplication::translate("OpticalFlowUI", "Frame i", 0));
        lblFrame1->setText(QApplication::translate("OpticalFlowUI", "TextLabel", 0));
        groupBox_6->setTitle(QApplication::translate("OpticalFlowUI", "Flow", 0));
        lblFlow->setText(QApplication::translate("OpticalFlowUI", "TextLabel", 0));
        groupBox_7->setTitle(QApplication::translate("OpticalFlowUI", "Frame i+1", 0));
        lblFrame2->setText(QApplication::translate("OpticalFlowUI", "TextLabel", 0));
        groupBox_3->setTitle(QApplication::translate("OpticalFlowUI", "Progress", 0));
        groupBox_4->setTitle(QString());
        label_6->setText(QApplication::translate("OpticalFlowUI", "Input dir: ", 0));
        txtInput->setText(QApplication::translate("OpticalFlowUI", "out/", 0));
        label_7->setText(QApplication::translate("OpticalFlowUI", "Output dir :", 0));
        txtOutput->setText(QApplication::translate("OpticalFlowUI", "out/flow/", 0));
        btStart->setText(QApplication::translate("OpticalFlowUI", "Start", 0));
        btPause->setText(QApplication::translate("OpticalFlowUI", "Pause", 0));
        btClose->setText(QApplication::translate("OpticalFlowUI", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class OpticalFlowUI: public Ui_OpticalFlowUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTICALFLOWUI_H
