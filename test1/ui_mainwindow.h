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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btClose;
    QLabel *label;
    QPushButton *btGo;
    QPushButton *btOpen;
    QLineEdit *txtFile;
    QLabel *lblImage;
    QPlainTextEdit *txtInfo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(538, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btClose = new QPushButton(centralWidget);
        btClose->setObjectName(QStringLiteral("btClose"));
        btClose->setGeometry(QRect(320, 220, 75, 23));
        btClose->setCheckable(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 140, 61, 16));
        btGo = new QPushButton(centralWidget);
        btGo->setObjectName(QStringLiteral("btGo"));
        btGo->setGeometry(QRect(200, 110, 75, 23));
        btOpen = new QPushButton(centralWidget);
        btOpen->setObjectName(QStringLiteral("btOpen"));
        btOpen->setGeometry(QRect(200, 70, 75, 23));
        txtFile = new QLineEdit(centralWidget);
        txtFile->setObjectName(QStringLiteral("txtFile"));
        txtFile->setGeometry(QRect(20, 70, 171, 20));
        lblImage = new QLabel(centralWidget);
        lblImage->setObjectName(QStringLiteral("lblImage"));
        lblImage->setGeometry(QRect(290, 10, 221, 191));
        txtInfo = new QPlainTextEdit(centralWidget);
        txtInfo->setObjectName(QStringLiteral("txtInfo"));
        txtInfo->setGeometry(QRect(20, 160, 281, 71));
        txtInfo->setReadOnly(true);
        txtInfo->setCenterOnScroll(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 538, 21));
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
        btClose->setText(QApplication::translate("MainWindow", "Close", 0));
        label->setText(QApplication::translate("MainWindow", "Media info :", 0));
        btGo->setText(QApplication::translate("MainWindow", "Go", 0));
        btOpen->setText(QApplication::translate("MainWindow", "Open file", 0));
        lblImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
