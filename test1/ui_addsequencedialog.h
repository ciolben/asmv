/********************************************************************************
** Form generated from reading UI file 'addsequencedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSEQUENCEDIALOG_H
#define UI_ADDSEQUENCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddSequenceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QListView *lstSequences;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *txtStart;
    QLabel *label_2;
    QLineEdit *txtEnd;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddSequenceDialog)
    {
        if (AddSequenceDialog->objectName().isEmpty())
            AddSequenceDialog->setObjectName(QStringLiteral("AddSequenceDialog"));
        AddSequenceDialog->resize(407, 325);
        verticalLayout = new QVBoxLayout(AddSequenceDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lstSequences = new QListView(AddSequenceDialog);
        lstSequences->setObjectName(QStringLiteral("lstSequences"));

        verticalLayout->addWidget(lstSequences);

        groupBox = new QGroupBox(AddSequenceDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 50));
        horizontalLayoutWidget = new QWidget(groupBox);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 0, 371, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        txtStart = new QLineEdit(horizontalLayoutWidget);
        txtStart->setObjectName(QStringLiteral("txtStart"));

        horizontalLayout->addWidget(txtStart);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        txtEnd = new QLineEdit(horizontalLayoutWidget);
        txtEnd->setObjectName(QStringLiteral("txtEnd"));

        horizontalLayout->addWidget(txtEnd);


        verticalLayout->addWidget(groupBox);

        pushButton = new QPushButton(AddSequenceDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(AddSequenceDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        buttonBox = new QDialogButtonBox(AddSequenceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddSequenceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddSequenceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddSequenceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddSequenceDialog);
    } // setupUi

    void retranslateUi(QDialog *AddSequenceDialog)
    {
        AddSequenceDialog->setWindowTitle(QApplication::translate("AddSequenceDialog", "Dialog", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("AddSequenceDialog", "Start :", 0));
        label_2->setText(QApplication::translate("AddSequenceDialog", "Stop :", 0));
        pushButton->setText(QApplication::translate("AddSequenceDialog", "Add", 0));
        pushButton_2->setText(QApplication::translate("AddSequenceDialog", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class AddSequenceDialog: public Ui_AddSequenceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSEQUENCEDIALOG_H
