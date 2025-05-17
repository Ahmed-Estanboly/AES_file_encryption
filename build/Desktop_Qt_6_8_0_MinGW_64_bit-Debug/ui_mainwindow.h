/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileCrypt
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *pathLineEdit;
    QPushButton *browseBotten;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *encryptButton;
    QRadioButton *decryptButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FileCrypt)
    {
        if (FileCrypt->objectName().isEmpty())
            FileCrypt->setObjectName("FileCrypt");
        FileCrypt->resize(670, 240);
        centralwidget = new QWidget(FileCrypt);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        pathLineEdit = new QLineEdit(centralwidget);
        pathLineEdit->setObjectName("pathLineEdit");

        horizontalLayout->addWidget(pathLineEdit);

        browseBotten = new QPushButton(centralwidget);
        browseBotten->setObjectName("browseBotten");

        horizontalLayout->addWidget(browseBotten);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        encryptButton = new QRadioButton(centralwidget);
        encryptButton->setObjectName("encryptButton");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        encryptButton->setFont(font1);

        horizontalLayout_2->addWidget(encryptButton);

        decryptButton = new QRadioButton(centralwidget);
        decryptButton->setObjectName("decryptButton");
        decryptButton->setFont(font1);

        horizontalLayout_2->addWidget(decryptButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        label_2->setFont(font2);

        horizontalLayout_3->addWidget(label_2);

        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");

        horizontalLayout_3->addWidget(passwordLineEdit);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout_6->addWidget(pushButton);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        horizontalLayout_6->addWidget(progressBar);


        gridLayout->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        FileCrypt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FileCrypt);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 670, 25));
        FileCrypt->setMenuBar(menubar);
        statusbar = new QStatusBar(FileCrypt);
        statusbar->setObjectName("statusbar");
        FileCrypt->setStatusBar(statusbar);

        retranslateUi(FileCrypt);

        QMetaObject::connectSlotsByName(FileCrypt);
    } // setupUi

    void retranslateUi(QMainWindow *FileCrypt)
    {
        FileCrypt->setWindowTitle(QCoreApplication::translate("FileCrypt", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("FileCrypt", "Enter the file path:", nullptr));
        browseBotten->setText(QCoreApplication::translate("FileCrypt", "Browse", nullptr));
        encryptButton->setText(QCoreApplication::translate("FileCrypt", "Encrypt", nullptr));
        decryptButton->setText(QCoreApplication::translate("FileCrypt", "Decrypt", nullptr));
        label_2->setText(QCoreApplication::translate("FileCrypt", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("FileCrypt", "Encrypt/Decrypt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileCrypt: public Ui_FileCrypt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
