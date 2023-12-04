/********************************************************************************
** Form generated from reading UI file 'makedeal.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEDEAL_H
#define UI_MAKEDEAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeDeal
{
public:
    QLabel *label;
    QLineEdit *lineEdit_clientID;
    QLabel *label_2;
    QLineEdit *lineEdit_name;
    QLabel *label_3;
    QLineEdit *lineEdit_login;
    QLabel *label_4;
    QLineEdit *lineEdit_password;
    QLabel *label_5;
    QLineEdit *lineEdit_passport;
    QLabel *label_6;
    QLineEdit *lineEdit_phone;
    QPushButton *pushButton_deal;

    void setupUi(QWidget *MakeDeal)
    {
        if (MakeDeal->objectName().isEmpty())
            MakeDeal->setObjectName(QString::fromUtf8("MakeDeal"));
        MakeDeal->resize(300, 200);
        label = new QLabel(MakeDeal);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 10, 61, 16));
        lineEdit_clientID = new QLineEdit(MakeDeal);
        lineEdit_clientID->setObjectName(QString::fromUtf8("lineEdit_clientID"));
        lineEdit_clientID->setGeometry(QRect(10, 30, 61, 24));
        label_2 = new QLabel(MakeDeal);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(91, 10, 81, 16));
        lineEdit_name = new QLineEdit(MakeDeal);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(90, 30, 201, 24));
        label_3 = new QLabel(MakeDeal);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(11, 80, 61, 16));
        lineEdit_login = new QLineEdit(MakeDeal);
        lineEdit_login->setObjectName(QString::fromUtf8("lineEdit_login"));
        lineEdit_login->setGeometry(QRect(10, 100, 81, 24));
        label_4 = new QLabel(MakeDeal);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(111, 80, 61, 16));
        lineEdit_password = new QLineEdit(MakeDeal);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(110, 100, 81, 24));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        label_5 = new QLabel(MakeDeal);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(211, 80, 101, 16));
        lineEdit_passport = new QLineEdit(MakeDeal);
        lineEdit_passport->setObjectName(QString::fromUtf8("lineEdit_passport"));
        lineEdit_passport->setGeometry(QRect(210, 100, 81, 24));
        label_6 = new QLabel(MakeDeal);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(11, 145, 61, 16));
        lineEdit_phone = new QLineEdit(MakeDeal);
        lineEdit_phone->setObjectName(QString::fromUtf8("lineEdit_phone"));
        lineEdit_phone->setGeometry(QRect(10, 165, 181, 24));
        pushButton_deal = new QPushButton(MakeDeal);
        pushButton_deal->setObjectName(QString::fromUtf8("pushButton_deal"));
        pushButton_deal->setGeometry(QRect(210, 165, 81, 24));

        retranslateUi(MakeDeal);

        QMetaObject::connectSlotsByName(MakeDeal);
    } // setupUi

    void retranslateUi(QWidget *MakeDeal)
    {
        MakeDeal->setWindowTitle(QCoreApplication::translate("MakeDeal", "Form", nullptr));
        label->setText(QCoreApplication::translate("MakeDeal", "ID \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("MakeDeal", "\320\244\320\230\320\236 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("MakeDeal", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_4->setText(QCoreApplication::translate("MakeDeal", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("MakeDeal", "\320\237\320\260\321\201\320\277\320\276\321\200\321\202", nullptr));
        label_6->setText(QCoreApplication::translate("MakeDeal", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275", nullptr));
        pushButton_deal->setText(QCoreApplication::translate("MakeDeal", "\320\241\320\264\320\265\320\273\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeDeal: public Ui_MakeDeal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEDEAL_H
