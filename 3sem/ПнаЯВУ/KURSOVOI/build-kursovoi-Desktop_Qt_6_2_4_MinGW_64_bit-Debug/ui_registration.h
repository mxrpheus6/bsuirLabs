/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_ID;
    QLabel *label_3;
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_phone;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_login;
    QLabel *label_6;
    QLineEdit *lineEdit_password;
    QLabel *label_7;
    QLineEdit *lineEdit_passport;
    QPushButton *pushButton_register;

    void setupUi(QWidget *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(360, 240);
        label = new QLabel(Registration);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(115, 10, 131, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label_2 = new QLabel(Registration);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 21, 16));
        lineEdit_ID = new QLineEdit(Registration);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(20, 80, 41, 24));
        label_3 = new QLabel(Registration);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 60, 121, 16));
        lineEdit_name = new QLineEdit(Registration);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(80, 80, 121, 24));
        lineEdit_phone = new QLineEdit(Registration);
        lineEdit_phone->setObjectName(QString::fromUtf8("lineEdit_phone"));
        lineEdit_phone->setGeometry(QRect(220, 80, 121, 24));
        label_4 = new QLabel(Registration);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(220, 60, 121, 16));
        label_5 = new QLabel(Registration);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(190, 120, 51, 16));
        lineEdit_login = new QLineEdit(Registration);
        lineEdit_login->setObjectName(QString::fromUtf8("lineEdit_login"));
        lineEdit_login->setGeometry(QRect(20, 140, 151, 24));
        label_6 = new QLabel(Registration);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 120, 41, 16));
        lineEdit_password = new QLineEdit(Registration);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(190, 140, 151, 24));
        lineEdit_password->setEchoMode(QLineEdit::Password);
        label_7 = new QLabel(Registration);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 180, 121, 16));
        lineEdit_passport = new QLineEdit(Registration);
        lineEdit_passport->setObjectName(QString::fromUtf8("lineEdit_passport"));
        lineEdit_passport->setGeometry(QRect(20, 200, 151, 24));
        pushButton_register = new QPushButton(Registration);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(190, 193, 151, 31));

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QWidget *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Form", nullptr));
        label->setText(QCoreApplication::translate("Registration", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "ID", nullptr));
        label_3->setText(QCoreApplication::translate("Registration", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\270 \320\270\320\275\320\270\321\206\320\270\320\260\320\273\321\213", nullptr));
        lineEdit_name->setText(QString());
        lineEdit_name->setPlaceholderText(QString());
        lineEdit_phone->setInputMask(QString());
        lineEdit_phone->setText(QString());
        lineEdit_phone->setPlaceholderText(QString());
        label_4->setText(QCoreApplication::translate("Registration", "\320\235\320\276\320\274\320\265\321\200 \321\202\320\265\320\273\320\265\321\204\320\276\320\275\320\260", nullptr));
        label_5->setText(QCoreApplication::translate("Registration", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        lineEdit_login->setPlaceholderText(QCoreApplication::translate("Registration", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274 6 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        label_6->setText(QCoreApplication::translate("Registration", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        lineEdit_password->setPlaceholderText(QCoreApplication::translate("Registration", "\320\234\320\270\320\275\320\270\320\274\321\203\320\274 8 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262", nullptr));
        label_7->setText(QCoreApplication::translate("Registration", "\320\235\320\276\320\274\320\265\321\200 \320\277\320\260\321\201\320\277\320\276\321\200\321\202\320\260", nullptr));
        lineEdit_passport->setInputMask(QString());
        lineEdit_passport->setText(QString());
        lineEdit_passport->setPlaceholderText(QString());
        pushButton_register->setText(QCoreApplication::translate("Registration", "\320\227\320\260\321\200\320\265\320\263\320\265\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
