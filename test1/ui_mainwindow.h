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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
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
    QPushButton *btTimeline;
    QPushButton *btFlow;
    QPushButton *btClose;
    QLineEdit *txtFile;
    QLineEdit *txtSkipFrames;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_4;
    QLineEdit *txtDuration;
    QLabel *label_3;
    QLineEdit *txtFrame;
    QLabel *label_2;
    QPushButton *btGo;
    QPushButton *btOpen;
    QLabel *label_7;
    QLabel *label;
    Timeline *wTimeline;
    QPlainTextEdit *txtInfo;
    QLabel *lblImage;
    QSlider *slider;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(833, 577);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btTimeline = new QPushButton(centralWidget);
        btTimeline->setObjectName(QStringLiteral("btTimeline"));

        gridLayout->addWidget(btTimeline, 8, 0, 1, 1);

        btFlow = new QPushButton(centralWidget);
        btFlow->setObjectName(QStringLiteral("btFlow"));

        gridLayout->addWidget(btFlow, 7, 0, 1, 1);

        btClose = new QPushButton(centralWidget);
        btClose->setObjectName(QStringLiteral("btClose"));
        btClose->setCheckable(false);

        gridLayout->addWidget(btClose, 7, 3, 1, 2);

        txtFile = new QLineEdit(centralWidget);
        txtFile->setObjectName(QStringLiteral("txtFile"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtFile->sizePolicy().hasHeightForWidth());
        txtFile->setSizePolicy(sizePolicy);

        gridLayout->addWidget(txtFile, 0, 0, 1, 3);

        txtSkipFrames = new QLineEdit(centralWidget);
        txtSkipFrames->setObjectName(QStringLiteral("txtSkipFrames"));
        sizePolicy.setHeightForWidth(txtSkipFrames->sizePolicy().hasHeightForWidth());
        txtSkipFrames->setSizePolicy(sizePolicy);

        gridLayout->addWidget(txtSkipFrames, 4, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 2, 1, 2);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        txtDuration = new QLineEdit(centralWidget);
        txtDuration->setObjectName(QStringLiteral("txtDuration"));
        sizePolicy.setHeightForWidth(txtDuration->sizePolicy().hasHeightForWidth());
        txtDuration->setSizePolicy(sizePolicy);
        txtDuration->setText(QStringLiteral("100"));

        gridLayout->addWidget(txtDuration, 3, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        txtFrame = new QLineEdit(centralWidget);
        txtFrame->setObjectName(QStringLiteral("txtFrame"));
        sizePolicy.setHeightForWidth(txtFrame->sizePolicy().hasHeightForWidth());
        txtFrame->setSizePolicy(sizePolicy);
        txtFrame->setText(QStringLiteral("15"));

        gridLayout->addWidget(txtFrame, 2, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        btGo = new QPushButton(centralWidget);
        btGo->setObjectName(QStringLiteral("btGo"));

        gridLayout->addWidget(btGo, 1, 3, 1, 2);

        btOpen = new QPushButton(centralWidget);
        btOpen->setObjectName(QStringLiteral("btOpen"));

        gridLayout->addWidget(btOpen, 0, 3, 1, 2);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 4, 2, 1, 3);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        wTimeline = new Timeline(centralWidget);
        wTimeline->setObjectName(QStringLiteral("wTimeline"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(wTimeline->sizePolicy().hasHeightForWidth());
        wTimeline->setSizePolicy(sizePolicy1);
        btFlow->raise();
        btTimeline->raise();
        btClose->raise();

        gridLayout->addWidget(wTimeline, 8, 1, 2, 5);

        txtInfo = new QPlainTextEdit(centralWidget);
        txtInfo->setObjectName(QStringLiteral("txtInfo"));
        sizePolicy.setHeightForWidth(txtInfo->sizePolicy().hasHeightForWidth());
        txtInfo->setSizePolicy(sizePolicy);
        txtInfo->setMinimumSize(QSize(0, 100));
        txtInfo->setMaximumSize(QSize(16777215, 100));
        txtInfo->setReadOnly(true);
        txtInfo->setCenterOnScroll(false);

        gridLayout->addWidget(txtInfo, 6, 0, 1, 5);

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

        slider = new QSlider(centralWidget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider, 7, 5, 1, 1, Qt::AlignTop);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        btTimeline->setText(QApplication::translate("MainWindow", "Timeline", 0));
        btFlow->setText(QApplication::translate("MainWindow", "OpticalFlow", 0));
        btClose->setText(QApplication::translate("MainWindow", "Close", 0));
        txtSkipFrames->setText(QApplication::translate("MainWindow", "5", 0));
        label_6->setText(QApplication::translate("MainWindow", "Save each ", 0));
        label_5->setText(QApplication::translate("MainWindow", "frames", 0));
        label_4->setText(QApplication::translate("MainWindow", "Seq duration :", 0));
        label_3->setText(QApplication::translate("MainWindow", "ms", 0));
        label_2->setText(QApplication::translate("MainWindow", "Time bw frame :", 0));
        btGo->setText(QApplication::translate("MainWindow", "Go", 0));
        btOpen->setText(QApplication::translate("MainWindow", "Open file", 0));
        label_7->setText(QApplication::translate("MainWindow", "frames to disk", 0));
        label->setText(QApplication::translate("MainWindow", "Media info :", 0));
        lblImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
