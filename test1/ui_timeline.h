/********************************************************************************
** Form generated from reading UI file 'timeline.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMELINE_H
#define UI_TIMELINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Timeline
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *Timeline)
    {
        if (Timeline->objectName().isEmpty())
            Timeline->setObjectName(QStringLiteral("Timeline"));
        Timeline->resize(400, 300);
        gridLayout = new QGridLayout(Timeline);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(Timeline);

        QMetaObject::connectSlotsByName(Timeline);
    } // setupUi

    void retranslateUi(QWidget *Timeline)
    {
        Timeline->setWindowTitle(QApplication::translate("Timeline", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Timeline: public Ui_Timeline {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINE_H
