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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
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
    QLabel *label_7;
    QLineEdit *txtFile;
    QDoubleSpinBox *sbReduction;
    QLineEdit *txtSkipFrames;
    Timeline *wTimeline;
    QLabel *label_3;
    QLineEdit *txtDuration;
    QLabel *label_5;
    QPushButton *btGo;
    QPushButton *btMotion;
    QSlider *slSpeed;
    QPushButton *btFlow;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QLabel *lblSplineInfo;
    QSlider *slOutliers;
    QDoubleSpinBox *spTolerance;
    QPushButton *pbRemoveOutliers;
    QPushButton *pbResetSpline;
    QLabel *label_2;
    QLineEdit *txtFrame;
    QPushButton *btClose;
    QPushButton *btInterpolate;
    QLabel *lblImage;
    QPushButton *pbFilter;
    QLabel *label_8;
    QPushButton *btOpen;
    QPlainTextEdit *txtInfo;
    QProgressBar *pbBuffer;
    QComboBox *cboBuffer;
    QLabel *label_4;
    QCheckBox *chkRemapped;
    QLabel *label;
    QPushButton *btTimeline;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(833, 577);
        MainWindow->setAnimated(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 4, 2, 1, 3);

        txtFile = new QLineEdit(centralWidget);
        txtFile->setObjectName(QStringLiteral("txtFile"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtFile->sizePolicy().hasHeightForWidth());
        txtFile->setSizePolicy(sizePolicy);
        txtFile->setMinimumSize(QSize(200, 0));
        txtFile->setReadOnly(true);

        gridLayout->addWidget(txtFile, 0, 0, 1, 3, Qt::AlignHCenter);

        sbReduction = new QDoubleSpinBox(centralWidget);
        sbReduction->setObjectName(QStringLiteral("sbReduction"));
        sbReduction->setSingleStep(0.5);

        gridLayout->addWidget(sbReduction, 14, 2, 1, 2);

        txtSkipFrames = new QLineEdit(centralWidget);
        txtSkipFrames->setObjectName(QStringLiteral("txtSkipFrames"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtSkipFrames->sizePolicy().hasHeightForWidth());
        txtSkipFrames->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(txtSkipFrames, 4, 1, 1, 1);

        wTimeline = new Timeline(centralWidget);
        wTimeline->setObjectName(QStringLiteral("wTimeline"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(wTimeline->sizePolicy().hasHeightForWidth());
        wTimeline->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(wTimeline, 8, 1, 5, 5);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        txtDuration = new QLineEdit(centralWidget);
        txtDuration->setObjectName(QStringLiteral("txtDuration"));
        sizePolicy1.setHeightForWidth(txtDuration->sizePolicy().hasHeightForWidth());
        txtDuration->setSizePolicy(sizePolicy1);
        txtDuration->setText(QStringLiteral("100"));

        gridLayout->addWidget(txtDuration, 3, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 2, 1, 2);

        btGo = new QPushButton(centralWidget);
        btGo->setObjectName(QStringLiteral("btGo"));

        gridLayout->addWidget(btGo, 1, 3, 1, 2);

        btMotion = new QPushButton(centralWidget);
        btMotion->setObjectName(QStringLiteral("btMotion"));

        gridLayout->addWidget(btMotion, 8, 0, 1, 1);

        slSpeed = new QSlider(centralWidget);
        slSpeed->setObjectName(QStringLiteral("slSpeed"));
        slSpeed->setMinimum(15);
        slSpeed->setMaximum(1000);
        slSpeed->setValue(500);
        slSpeed->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slSpeed, 7, 5, 1, 1, Qt::AlignTop);

        btFlow = new QPushButton(centralWidget);
        btFlow->setObjectName(QStringLiteral("btFlow"));

        gridLayout->addWidget(btFlow, 7, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

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


        gridLayout->addLayout(horizontalLayout, 14, 5, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        txtFrame = new QLineEdit(centralWidget);
        txtFrame->setObjectName(QStringLiteral("txtFrame"));
        sizePolicy1.setHeightForWidth(txtFrame->sizePolicy().hasHeightForWidth());
        txtFrame->setSizePolicy(sizePolicy1);
        txtFrame->setText(QStringLiteral("5"));

        gridLayout->addWidget(txtFrame, 2, 1, 1, 1);

        btClose = new QPushButton(centralWidget);
        btClose->setObjectName(QStringLiteral("btClose"));
        btClose->setCheckable(false);

        gridLayout->addWidget(btClose, 7, 3, 1, 2);

        btInterpolate = new QPushButton(centralWidget);
        btInterpolate->setObjectName(QStringLiteral("btInterpolate"));

        gridLayout->addWidget(btInterpolate, 7, 1, 1, 1);

        lblImage = new QLabel(centralWidget);
        lblImage->setObjectName(QStringLiteral("lblImage"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lblImage->sizePolicy().hasHeightForWidth());
        lblImage->setSizePolicy(sizePolicy3);
        lblImage->setMinimumSize(QSize(0, 255));
        lblImage->setFrameShape(QFrame::Box);

        gridLayout->addWidget(lblImage, 0, 5, 7, 1, Qt::AlignTop);

        pbFilter = new QPushButton(centralWidget);
        pbFilter->setObjectName(QStringLiteral("pbFilter"));

        gridLayout->addWidget(pbFilter, 11, 0, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 14, 1, 1, 1);

        btOpen = new QPushButton(centralWidget);
        btOpen->setObjectName(QStringLiteral("btOpen"));

        gridLayout->addWidget(btOpen, 0, 3, 1, 2);

        txtInfo = new QPlainTextEdit(centralWidget);
        txtInfo->setObjectName(QStringLiteral("txtInfo"));
        sizePolicy1.setHeightForWidth(txtInfo->sizePolicy().hasHeightForWidth());
        txtInfo->setSizePolicy(sizePolicy1);
        txtInfo->setMinimumSize(QSize(0, 100));
        txtInfo->setMaximumSize(QSize(16777215, 100));
        txtInfo->setReadOnly(true);
        txtInfo->setCenterOnScroll(false);

        gridLayout->addWidget(txtInfo, 6, 0, 1, 5);

        pbBuffer = new QProgressBar(centralWidget);
        pbBuffer->setObjectName(QStringLiteral("pbBuffer"));
        pbBuffer->setMaximum(3);
        pbBuffer->setValue(0);
        pbBuffer->setOrientation(Qt::Vertical);

        gridLayout->addWidget(pbBuffer, 12, 0, 1, 1);

        cboBuffer = new QComboBox(centralWidget);
        cboBuffer->setObjectName(QStringLiteral("cboBuffer"));
        cboBuffer->setEditable(false);
        cboBuffer->setMaxVisibleItems(15);

        gridLayout->addWidget(cboBuffer, 14, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        chkRemapped = new QCheckBox(centralWidget);
        chkRemapped->setObjectName(QStringLiteral("chkRemapped"));

        gridLayout->addWidget(chkRemapped, 1, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        btTimeline = new QPushButton(centralWidget);
        btTimeline->setObjectName(QStringLiteral("btTimeline"));

        gridLayout->addWidget(btTimeline, 10, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ASMV", 0));
        label_7->setText(QApplication::translate("MainWindow", "frames to disk", 0));
        txtFile->setText(QApplication::translate("MainWindow", "C:\\Users\\Loic\\ppt-24.s03e01.avi", 0));
        txtSkipFrames->setText(QApplication::translate("MainWindow", "0", 0));
        label_3->setText(QApplication::translate("MainWindow", "ms", 0));
        label_5->setText(QApplication::translate("MainWindow", "frames", 0));
        btGo->setText(QApplication::translate("MainWindow", "Play", 0));
        btMotion->setText(QApplication::translate("MainWindow", "Motion", 0));
        btFlow->setText(QApplication::translate("MainWindow", "OpticalFlow", 0));
        label_6->setText(QApplication::translate("MainWindow", "Save each ", 0));
        lblSplineInfo->setText(QApplication::translate("MainWindow", "...", 0));
        pbRemoveOutliers->setText(QApplication::translate("MainWindow", "Remove Outliers", 0));
        pbResetSpline->setText(QApplication::translate("MainWindow", "Reset Spline", 0));
        label_2->setText(QApplication::translate("MainWindow", "Time bw frame :", 0));
        btClose->setText(QApplication::translate("MainWindow", "Close", 0));
        btInterpolate->setText(QApplication::translate("MainWindow", "Interpolate", 0));
        lblImage->setText(QString());
        pbFilter->setText(QApplication::translate("MainWindow", "Add Filter", 0));
        label_8->setText(QApplication::translate("MainWindow", "Reduce number of keys by ", 0));
        btOpen->setText(QApplication::translate("MainWindow", "Open file", 0));
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
        label_4->setText(QApplication::translate("MainWindow", "Seq duration :", 0));
        chkRemapped->setText(QApplication::translate("MainWindow", "Play remapped video", 0));
        label->setText(QApplication::translate("MainWindow", "Player info :", 0));
        btTimeline->setText(QApplication::translate("MainWindow", "Add sequence", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
