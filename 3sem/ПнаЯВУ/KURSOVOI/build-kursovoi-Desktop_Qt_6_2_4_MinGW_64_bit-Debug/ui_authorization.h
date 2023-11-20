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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Authorization
{
public:
    QGridLayout *gridLayout;
    QLabel *label_auth_pic;
    QLabel *label_auth;
    QHBoxLayout *horizontalLayout;
    QLabel *label_username;
    QLineEdit *lineEdit_username;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_password;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;

    void setupUi(QWidget *Authorization)
    {
        if (Authorization->objectName().isEmpty())
            Authorization->setObjectName(QString::fromUtf8("Authorization"));
        Authorization->resize(400, 270);
        Authorization->setMinimumSize(QSize(400, 270));
        Authorization->setMaximumSize(QSize(400, 270));
        gridLayout = new QGridLayout(Authorization);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_auth_pic = new QLabel(Authorization);
        label_auth_pic->setObjectName(QString::fromUtf8("label_auth_pic"));
        label_auth_pic->setMinimumSize(QSize(152, 78));
        label_auth_pic->setMaximumSize(QSize(152, 78));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Black")});
        font.setPointSize(26);
        font.setBold(true);
        label_auth_pic->setFont(font);
        label_auth_pic->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_auth_pic, 0, 0, 1, 1);

        label_auth = new QLabel(Authorization);
        label_auth->setObjectName(QString::fromUtf8("label_auth"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        label_auth->setFont(font1);
        label_auth->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_auth, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_username = new QLabel(Authorization);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        label_username->setFont(font2);

        horizontalLayout->addWidget(label_username);

        lineEdit_username = new QLineEdit(Authorization);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setMinimumSize(QSize(0, 30));
        lineEdit_username->setFrame(false);

        horizontalLayout->addWidget(lineEdit_username);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_password = new QLabel(Authorization);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setFont(font2);

        horizontalLayout_2->addWidget(label_password);

        lineEdit_password = new QLineEdit(Authorization);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setMinimumSize(QSize(0, 30));
        lineEdit_password->setFrame(false);
        lineEdit_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_password);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 2);

        pushButton_login = new QPushButton(Authorization);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Cascadia Mono")});
        font3.setPointSize(14);
        font3.setBold(false);
        pushButton_login->setFont(font3);
        pushButton_login->setAutoDefault(false);

        gridLayout->addWidget(pushButton_login, 3, 0, 1, 2);


        retranslateUi(Authorization);

        pushButton_login->setDefault(false);


        QMetaObject::connectSlotsByName(Authorization);
    } // setupUi

    void retranslateUi(QWidget *Authorization)
    {
        Authorization->setWindowTitle(QCoreApplication::translate("Authorization", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_auth_pic->setText(QString());
        label_auth->setText(QCoreApplication::translate("Authorization", "\320\222\320\276\320\271\321\202\320\270 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        label_username->setText(QCoreApplication::translate("Authorization", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_password->setText(QCoreApplication::translate("Authorization", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Authorization", "\320\222\320\276\320\271\321\202\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Authorization: public Ui_Authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
