/********************************************************************************
** Form generated from reading UI file 'requests.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REQUESTS_H
#define UI_REQUESTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Requests
{
public:
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Requests)
    {
        if (Requests->objectName().isEmpty())
            Requests->setObjectName(QString::fromUtf8("Requests"));
        Requests->resize(550, 450);
        tableView = new QTableView(Requests);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 10, 531, 361));
        pushButton = new QPushButton(Requests);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(420, 380, 121, 55));
        pushButton_2 = new QPushButton(Requests);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 380, 121, 55));

        retranslateUi(Requests);

        QMetaObject::connectSlotsByName(Requests);
    } // setupUi

    void retranslateUi(QWidget *Requests)
    {
        Requests->setWindowTitle(QCoreApplication::translate("Requests", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Requests", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Requests", "\320\232\320\260\321\200\321\202\320\276\321\207\320\272\320\260 \320\276\320\261\321\212\320\265\320\272\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Requests: public Ui_Requests {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REQUESTS_H
