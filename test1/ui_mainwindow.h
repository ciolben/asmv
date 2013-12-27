/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "timeline.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *btFilter;
    QDial *dialFit;
    QDial *dialMod;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_11;
    QLabel *lblMod;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QLabel *lblFit;
    QCheckBox *chkPlus;
    QCheckBox *chkCut;
    Timeline *wTimeline;
    QPushButton *btInterpolate;
    QLabel *lblImage;
    QPushButton *btMotion;
    QPushButton *btFlow;
    QLabel *label_12;
    QDoubleSpinBox *sbReduction;
    QLineEdit *txtDuration;
    QHBoxLayout *horizontalLayout;
    QLabel *lblSplineInfo;
    QSlider *slOutliers;
    QDoubleSpinBox *spTolerance;
    QPushButton *pbRemoveOutliers;
    QPushButton *pbResetSpline;
    QLabel *label_5;
    QPushButton *btClose;
    QPushButton *btOpen;
    QSlider *slSpeed;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *btGo;
    QLineEdit *txtFile;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label;
    QLineEdit *txtSkipFrames;
    QLineEdit *txtFrame;
    QSpacerItem *horizontalSpacer;
    QCheckBox *chkRemapped;
    QLabel *label_4;
    QLabel *label_8;
    QProgressBar *pbBuffer;
    QLabel *label_7;
    QComboBox *cboBuffer;
    QPlainTextEdit *txtInfo;
    QPushButton *btTimeline;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtFit;
    QPushButton *btFit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(838, 706);
        MainWindow->setAnimated(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btFilter = new QPushButton(groupBox);
        btFilter->setObjectName(QStringLiteral("btFilter"));

        gridLayout_2->addWidget(btFilter, 1, 2, 1, 1);

        dialFit = new QDial(groupBox);
        dialFit->setObjectName(QStringLiteral("dialFit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dialFit->sizePolicy().hasHeightForWidth());
        dialFit->setSizePolicy(sizePolicy);
        dialFit->setMaximumSize(QSize(200, 100));
        dialFit->setNotchTarget(2.7);
        dialFit->setNotchesVisible(true);

        gridLayout_2->addWidget(dialFit, 1, 1, 1, 1);

        dialMod = new QDial(groupBox);
        dialMod->setObjectName(QStringLiteral("dialMod"));
        sizePolicy.setHeightForWidth(dialMod->sizePolicy().hasHeightForWidth());
        dialMod->setSizePolicy(sizePolicy);
        dialMod->setMaximumSize(QSize(200, 100));
        dialMod->setMinimum(1);
        dialMod->setMaximum(3);
        dialMod->setPageStep(1);
        dialMod->setTracking(true);
        dialMod->setOrientation(Qt::Horizontal);
        dialMod->setInvertedAppearance(false);
        dialMod->setWrapping(false);
        dialMod->setNotchesVisible(true);

        gridLayout_2->addWidget(dialMod, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_2->addWidget(label_11);

        lblMod = new QLabel(groupBox);
        lblMod->setObjectName(QStringLiteral("lblMod"));

        horizontalLayout_2->addWidget(lblMod);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMaximumSize(QSize(16777215, 16777215));
        label_10->setFrameShape(QFrame::NoFrame);
        label_10->setScaledContents(false);
        label_10->setWordWrap(false);

        horizontalLayout_3->addWidget(label_10);

        lblFit = new QLabel(groupBox);
        lblFit->setObjectName(QStringLiteral("lblFit"));

        horizontalLayout_3->addWidget(lblFit);

        chkPlus = new QCheckBox(groupBox);
        chkPlus->setObjectName(QStringLiteral("chkPlus"));

        horizontalLayout_3->addWidget(chkPlus);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        chkCut = new QCheckBox(groupBox);
        chkCut->setObjectName(QStringLiteral("chkCut"));
        chkCut->setChecked(true);

        gridLayout_2->addWidget(chkCut, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox, 18, 5, 1, 1);

        wTimeline = new Timeline(centralWidget);
        wTimeline->setObjectName(QStringLiteral("wTimeline"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wTimeline->sizePolicy().hasHeightForWidth());
        wTimeline->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(wTimeline, 9, 1, 7, 5);

        btInterpolate = new QPushButton(centralWidget);
        btInterpolate->setObjectName(QStringLiteral("btInterpolate"));

        gridLayout->addWidget(btInterpolate, 8, 1, 1, 1);

        lblImage = new QLabel(centralWidget);
        lblImage->setObjectName(QStringLiteral("lblImage"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblImage->sizePolicy().hasHeightForWidth());
        lblImage->setSizePolicy(sizePolicy2);
        lblImage->setMinimumSize(QSize(0, 255));
        lblImage->setFrameShape(QFrame::Box);

        gridLayout->addWidget(lblImage, 0, 5, 7, 1, Qt::AlignTop);

        btMotion = new QPushButton(centralWidget);
        btMotion->setObjectName(QStringLiteral("btMotion"));

        gridLayout->addWidget(btMotion, 9, 0, 1, 1);

        btFlow = new QPushButton(centralWidget);
        btFlow->setObjectName(QStringLiteral("btFlow"));

        gridLayout->addWidget(btFlow, 8, 0, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_12, 18, 1, 1, 1);

        sbReduction = new QDoubleSpinBox(centralWidget);
        sbReduction->setObjectName(QStringLiteral("sbReduction"));
        sbReduction->setSingleStep(0.5);

        gridLayout->addWidget(sbReduction, 17, 2, 1, 2);

        txtDuration = new QLineEdit(centralWidget);
        txtDuration->setObjectName(QStringLiteral("txtDuration"));
        sizePolicy.setHeightForWidth(txtDuration->sizePolicy().hasHeightForWidth());
        txtDuration->setSizePolicy(sizePolicy);
        txtDuration->setText(QStringLiteral("100"));

        gridLayout->addWidget(txtDuration, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblSplineInfo = new QLabel(centralWidget);
        lblSplineInfo->setObjectName(QStringLiteral("lblSplineInfo"));
        lblSplineInfo->setMinimumSize(QSize(200, 0));
        lblSplineInfo->setLineWidth(1);
        lblSplineInfo->setMargin(0);
        lblSplineInfo->setIndent(-1);

        horizontalLayout->addWidget(lblSplineInfo, 0, Qt::AlignLeft);

        slOutliers = new QSlider(centralWidget);
        slOutliers->setObjectName(QStringLiteral("slOutliers"));
        slOutliers->setMaximumSize(QSize(50, 16777215));
        slOutliers->setMinimum(1);
        slOutliers->setMaximum(99);
        slOutliers->setValue(50);
        slOutliers->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(slOutliers);

        spTolerance = new QDoubleSpinBox(centralWidget);
        spTolerance->setObjectName(QStringLiteral("spTolerance"));
        spTolerance->setMaximum(9999);

        horizontalLayout->addWidget(spTolerance);

        pbRemoveOutliers = new QPushButton(centralWidget);
        pbRemoveOutliers->setObjectName(QStringLiteral("pbRemoveOutliers"));
        pbRemoveOutliers->setMaximumSize(QSize(100, 16777215));
        pbRemoveOutliers->setDefault(false);
        pbRemoveOutliers->setFlat(false);

        horizontalLayout->addWidget(pbRemoveOutliers);

        pbResetSpline = new QPushButton(centralWidget);
        pbResetSpline->setObjectName(QStringLiteral("pbResetSpline"));
        pbResetSpline->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pbResetSpline);


        gridLayout->addLayout(horizontalLayout, 17, 5, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 2, 1, 2);

        btClose = new QPushButton(centralWidget);
        btClose->setObjectName(QStringLiteral("btClose"));
        btClose->setCheckable(false);

        gridLayout->addWidget(btClose, 8, 3, 1, 2);

        btOpen = new QPushButton(centralWidget);
        btOpen->setObjectName(QStringLiteral("btOpen"));

        gridLayout->addWidget(btOpen, 0, 3, 1, 2);

        slSpeed = new QSlider(centralWidget);
        slSpeed->setObjectName(QStringLiteral("slSpeed"));
        slSpeed->setMinimum(15);
        slSpeed->setMaximum(1000);
        slSpeed->setValue(500);
        slSpeed->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slSpeed, 8, 5, 1, 1, Qt::AlignTop);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        btGo = new QPushButton(centralWidget);
        btGo->setObjectName(QStringLiteral("btGo"));

        gridLayout->addWidget(btGo, 1, 3, 1, 2);

        txtFile = new QLineEdit(centralWidget);
        txtFile->setObjectName(QStringLiteral("txtFile"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(txtFile->sizePolicy().hasHeightForWidth());
        txtFile->setSizePolicy(sizePolicy3);
        txtFile->setMinimumSize(QSize(200, 0));
        txtFile->setReadOnly(true);

        gridLayout->addWidget(txtFile, 0, 0, 1, 3, Qt::AlignHCenter);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 13, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        txtSkipFrames = new QLineEdit(centralWidget);
        txtSkipFrames->setObjectName(QStringLiteral("txtSkipFrames"));
        sizePolicy.setHeightForWidth(txtSkipFrames->sizePolicy().hasHeightForWidth());
        txtSkipFrames->setSizePolicy(sizePolicy);

        gridLayout->addWidget(txtSkipFrames, 4, 1, 1, 1);

        txtFrame = new QLineEdit(centralWidget);
        txtFrame->setObjectName(QStringLiteral("txtFrame"));
        sizePolicy.setHeightForWidth(txtFrame->sizePolicy().hasHeightForWidth());
        txtFrame->setSizePolicy(sizePolicy);
        txtFrame->setText(QStringLiteral("5"));

        gridLayout->addWidget(txtFrame, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 4, 1, 1);

        chkRemapped = new QCheckBox(centralWidget);
        chkRemapped->setObjectName(QStringLiteral("chkRemapped"));

        gridLayout->addWidget(chkRemapped, 1, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 17, 1, 1, 1);

        pbBuffer = new QProgressBar(centralWidget);
        pbBuffer->setObjectName(QStringLiteral("pbBuffer"));
        pbBuffer->setMinimumSize(QSize(0, 100));
        pbBuffer->setMaximumSize(QSize(16777215, 200));
        pbBuffer->setMaximum(3);
        pbBuffer->setValue(0);
        pbBuffer->setOrientation(Qt::Vertical);

        gridLayout->addWidget(pbBuffer, 15, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 4, 2, 1, 3);

        cboBuffer = new QComboBox(centralWidget);
        cboBuffer->setObjectName(QStringLiteral("cboBuffer"));
        cboBuffer->setEditable(false);
        cboBuffer->setMaxVisibleItems(15);

        gridLayout->addWidget(cboBuffer, 17, 0, 1, 1);

        txtInfo = new QPlainTextEdit(centralWidget);
        txtInfo->setObjectName(QStringLiteral("txtInfo"));
        sizePolicy.setHeightForWidth(txtInfo->sizePolicy().hasHeightForWidth());
        txtInfo->setSizePolicy(sizePolicy);
        txtInfo->setMinimumSize(QSize(0, 100));
        txtInfo->setMaximumSize(QSize(16777215, 100));
        txtInfo->setReadOnly(true);
        txtInfo->setCenterOnScroll(false);

        gridLayout->addWidget(txtInfo, 6, 0, 1, 5);

        btTimeline = new QPushButton(centralWidget);
        btTimeline->setObjectName(QStringLiteral("btTimeline"));

        gridLayout->addWidget(btTimeline, 11, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 84);
        txtFit = new QLineEdit(centralWidget);
        txtFit->setObjectName(QStringLiteral("txtFit"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(txtFit->sizePolicy().hasHeightForWidth());
        txtFit->setSizePolicy(sizePolicy4);
        txtFit->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_5->addWidget(txtFit);

        btFit = new QPushButton(centralWidget);
        btFit->setObjectName(QStringLiteral("btFit"));
        sizePolicy.setHeightForWidth(btFit->sizePolicy().hasHeightForWidth());
        btFit->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(btFit);


        gridLayout->addLayout(horizontalLayout_5, 18, 2, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 838, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(dialMod, SIGNAL(valueChanged(int)), lblMod, SLOT(setNum(int)));
        QObject::connect(dialFit, SIGNAL(valueChanged(int)), lblFit, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ASMV", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Filter", 0));
        btFilter->setText(QApplication::translate("MainWindow", "Add Filter", 0));
        label_11->setText(QApplication::translate("MainWindow", "Mod(1,2,3) :", 0));
        lblMod->setText(QApplication::translate("MainWindow", "1", 0));
        label_10->setText(QApplication::translate("MainWindow", "Fit :", 0));
        lblFit->setText(QApplication::translate("MainWindow", "0", 0));
        chkPlus->setText(QApplication::translate("MainWindow", "+", 0));
        chkCut->setText(QApplication::translate("MainWindow", "Cut too high values", 0));
        btInterpolate->setText(QApplication::translate("MainWindow", "Interpolate", 0));
        lblImage->setText(QString());
        btMotion->setText(QApplication::translate("MainWindow", "Motion", 0));
        btFlow->setText(QApplication::translate("MainWindow", "OpticalFlow", 0));
        label_12->setText(QApplication::translate("MainWindow", "Fit factor :", 0));
        lblSplineInfo->setText(QApplication::translate("MainWindow", "...", 0));
        pbRemoveOutliers->setText(QApplication::translate("MainWindow", "Remove Outliers", 0));
        pbResetSpline->setText(QApplication::translate("MainWindow", "Reset Spline", 0));
        label_5->setText(QApplication::translate("MainWindow", "frames", 0));
        btClose->setText(QApplication::translate("MainWindow", "Close", 0));
        btOpen->setText(QApplication::translate("MainWindow", "Open file", 0));
        label_3->setText(QApplication::translate("MainWindow", "ms", 0));
        label_2->setText(QApplication::translate("MainWindow", "Time bw frame :", 0));
        btGo->setText(QApplication::translate("MainWindow", "Play", 0));
        txtFile->setText(QApplication::translate("MainWindow", "C:\\Users\\Loic\\ppt-24.s03e01.avi", 0));
        label_9->setText(QApplication::translate("MainWindow", "Buffer usage :", 0));
        label_6->setText(QApplication::translate("MainWindow", "Save each ", 0));
        label->setText(QApplication::translate("MainWindow", "Player info :", 0));
        txtSkipFrames->setText(QApplication::translate("MainWindow", "0", 0));
        chkRemapped->setText(QApplication::translate("MainWindow", "Play remapped video", 0));
        label_4->setText(QApplication::translate("MainWindow", "Seq duration :", 0));
        label_8->setText(QApplication::translate("MainWindow", "Reduce number of keys by ", 0));
        label_7->setText(QApplication::translate("MainWindow", "frames to disk", 0));
        cboBuffer->clear();
        cboBuffer->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "3", 0)
         << QApplication::translate("MainWindow", "1", 0)
         << QApplication::translate("MainWindow", "2", 0)
         << QApplication::translate("MainWindow", "4", 0)
         << QApplication::translate("MainWindow", "5", 0)
         << QApplication::translate("MainWindow", "6", 0)
         << QApplication::translate("MainWindow", "7", 0)
         << QApplication::translate("MainWindow", "8", 0)
         << QApplication::translate("MainWindow", "9", 0)
         << QApplication::translate("MainWindow", "10", 0)
         << QApplication::translate("MainWindow", "11", 0)
         << QApplication::translate("MainWindow", "12", 0)
         << QApplication::translate("MainWindow", "13", 0)
         << QApplication::translate("MainWindow", "14", 0)
         << QApplication::translate("MainWindow", "15", 0)
         << QApplication::translate("MainWindow", "16", 0)
         << QApplication::translate("MainWindow", "17", 0)
         << QApplication::translate("MainWindow", "18", 0)
         << QApplication::translate("MainWindow", "19", 0)
         << QApplication::translate("MainWindow", "20", 0)
        );
        btTimeline->setText(QApplication::translate("MainWindow", "Add sequence", 0));
        txtFit->setText(QApplication::translate("MainWindow", "0", 0));
        btFit->setText(QApplication::translate("MainWindow", "Fit", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
