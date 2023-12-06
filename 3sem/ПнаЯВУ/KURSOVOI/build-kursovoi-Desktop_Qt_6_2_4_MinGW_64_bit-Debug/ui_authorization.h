/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authorization
{
public:
    QLabel *label_auth_pic;
    QLabel *label_auth;
    QPushButton *pushButton_login;
    QLineEdit *lineEditUsername;
    QLabel *labelUsername;
    QLineEdit *lineEditPassword;
    QLabel *labelPassword;
    QPushButton *pushButton_register;
    QLabel *label;

    void setupUi(QWidget *Authorization)
    {
        if (Authorization->objectName().isEmpty())
            Authorization->setObjectName(QString::fromUtf8("Authorization"));
        Authorization->resize(400, 270);
        Authorization->setMinimumSize(QSize(400, 270));
        Authorization->setMaximumSize(QSize(400, 270));
        label_auth_pic = new QLabel(Authorization);
        label_auth_pic->setObjectName(QString::fromUtf8("label_auth_pic"));
        label_auth_pic->setGeometry(QRect(10, 20, 152, 78));
        label_auth_pic->setMinimumSize(QSize(152, 78));
        label_auth_pic->setMaximumSize(QSize(152, 78));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Black")});
        font.setPointSize(26);
        font.setBold(true);
        label_auth_pic->setFont(font);
        label_auth_pic->setAlignment(Qt::AlignCenter);
        label_auth = new QLabel(Authorization);
        label_auth->setObjectName(QString::fromUtf8("label_auth"));
        label_auth->setGeometry(QRect(200, 40, 174, 24));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        label_auth->setFont(font1);
        label_auth->setAlignment(Qt::AlignCenter);
        pushButton_login = new QPushButton(Authorization);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(140, 200, 251, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Cascadia Mono")});
        font2.setPointSize(14);
        font2.setBold(false);
        pushButton_login->setFont(font2);
        pushButton_login->setAutoDefault(false);
        lineEditUsername = new QLineEdit(Authorization);
        lineEditUsername->setObjectName(QString::fromUtf8("lineEditUsername"));
        lineEditUsername->setGeometry(QRect(165, 110, 226, 30));
        lineEditUsername->setMinimumSize(QSize(0, 30));
        lineEditUsername->setFrame(false);
        labelUsername = new QLabel(Authorization);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));
        labelUsername->setGeometry(QRect(10, 110, 151, 30));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        font3.setBold(true);
        labelUsername->setFont(font3);
        lineEditPassword = new QLineEdit(Authorization);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setGeometry(QRect(80, 155, 311, 30));
        lineEditPassword->setMinimumSize(QSize(0, 30));
        lineEditPassword->setFrame(false);
        lineEditPassword->setEchoMode(QLineEdit::Password);
        labelPassword = new QLabel(Authorization);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));
        labelPassword->setGeometry(QRect(10, 156, 61, 30));
        labelPassword->setFont(font3);
        pushButton_register = new QPushButton(Authorization);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(10, 230, 121, 31));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Cascadia Mono")});
        font4.setPointSize(12);
        font4.setBold(false);
        pushButton_register->setFont(font4);
        pushButton_register->setAutoDefault(false);
        label = new QLabel(Authorization);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(12, 210, 91, 16));

        retranslateUi(Authorization);

        pushButton_login->setDefault(false);
        pushButton_register->setDefault(false);


        QMetaObject::connectSlotsByName(Authorization);
    } // setupUi

    void retranslateUi(QWidget *Authorization)
    {
        Authorization->setWindowTitle(QCoreApplication::translate("Authorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_auth_pic->setText(QString());
        label_auth->setText(QCoreApplication::translate("Authorization", "\320\222\320\276\320\271\321\202\320\270 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Authorization", "\320\222\320\276\320\271\321\202\320\270", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_login->setShortcut(QCoreApplication::translate("Authorization", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        labelUsername->setText(QCoreApplication::translate("Authorization", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        labelPassword->setText(QCoreApplication::translate("Authorization", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton_register->setText(QCoreApplication::translate("Authorization", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        label->setText(QCoreApplication::translate("Authorization", "\320\222 \320\277\320\265\321\200\320\262\321\213\320\271 \321\200\320\260\320\267?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authorization: public Ui_Authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
