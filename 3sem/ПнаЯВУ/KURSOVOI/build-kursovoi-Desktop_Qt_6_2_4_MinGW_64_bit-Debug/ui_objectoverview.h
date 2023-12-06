/********************************************************************************
** Form generated from reading UI file 'objectoverview.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTOVERVIEW_H
#define UI_OBJECTOVERVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_objectOverview
{
public:
    QLabel *label_deal;
    QComboBox *comboBox_deal;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit_description;
    QTableView *tableView_extended;
    QLabel *label_3;
    QLineEdit *lineEdit_address;
    QLabel *label_4;
    QComboBox *comboBox_district;
    QLabel *label_5;
    QLineEdit *lineEdit_ID;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_price;
    QLabel *label_rieltor;
    QComboBox *comboBox_rieltor;
    QLabel *label_9;
    QLineEdit *lineEdit_square;
    QLineEdit *lineEdit_floor_amount;
    QLabel *label_10;
    QLineEdit *lineEdit_year;
    QLabel *label_11;
    QComboBox *comboBox_client;
    QLabel *label_client;
    QPushButton *pushButton_save;
    QPushButton *pushButton_deal;
    QLineEdit *lineEdit_type;
    QCheckBox *checkBox_deal;
    QCheckBox *checkBox_auth;
    QPushButton *pushButton_request;

    void setupUi(QWidget *objectOverview)
    {
        if (objectOverview->objectName().isEmpty())
            objectOverview->setObjectName(QString::fromUtf8("objectOverview"));
        objectOverview->resize(500, 400);
        objectOverview->setMaximumSize(QSize(500, 400));
        label_deal = new QLabel(objectOverview);
        label_deal->setObjectName(QString::fromUtf8("label_deal"));
        label_deal->setGeometry(QRect(230, 260, 71, 21));
        comboBox_deal = new QComboBox(objectOverview);
        comboBox_deal->setObjectName(QString::fromUtf8("comboBox_deal"));
        comboBox_deal->setGeometry(QRect(300, 260, 181, 20));
        label_2 = new QLabel(objectOverview);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 61, 16));
        plainTextEdit_description = new QPlainTextEdit(objectOverview);
        plainTextEdit_description->setObjectName(QString::fromUtf8("plainTextEdit_description"));
        plainTextEdit_description->setGeometry(QRect(20, 80, 201, 61));
        tableView_extended = new QTableView(objectOverview);
        tableView_extended->setObjectName(QString::fromUtf8("tableView_extended"));
        tableView_extended->setGeometry(QRect(230, 10, 251, 241));
        label_3 = new QLabel(objectOverview);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 190, 41, 16));
        lineEdit_address = new QLineEdit(objectOverview);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));
        lineEdit_address->setGeometry(QRect(90, 190, 131, 20));
        label_4 = new QLabel(objectOverview);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 154, 41, 16));
        comboBox_district = new QComboBox(objectOverview);
        comboBox_district->setObjectName(QString::fromUtf8("comboBox_district"));
        comboBox_district->setGeometry(QRect(90, 150, 131, 24));
        label_5 = new QLabel(objectOverview);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 10, 111, 16));
        lineEdit_ID = new QLineEdit(objectOverview);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(20, 30, 51, 24));
        label_6 = new QLabel(objectOverview);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 10, 16, 17));
        label_7 = new QLabel(objectOverview);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(21, 225, 61, 31));
        lineEdit_price = new QLineEdit(objectOverview);
        lineEdit_price->setObjectName(QString::fromUtf8("lineEdit_price"));
        lineEdit_price->setGeometry(QRect(130, 230, 91, 20));
        label_rieltor = new QLabel(objectOverview);
        label_rieltor->setObjectName(QString::fromUtf8("label_rieltor"));
        label_rieltor->setGeometry(QRect(230, 330, 51, 17));
        comboBox_rieltor = new QComboBox(objectOverview);
        comboBox_rieltor->setObjectName(QString::fromUtf8("comboBox_rieltor"));
        comboBox_rieltor->setGeometry(QRect(280, 330, 201, 20));
        label_9 = new QLabel(objectOverview);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 255, 81, 31));
        lineEdit_square = new QLineEdit(objectOverview);
        lineEdit_square->setObjectName(QString::fromUtf8("lineEdit_square"));
        lineEdit_square->setGeometry(QRect(130, 260, 91, 20));
        lineEdit_floor_amount = new QLineEdit(objectOverview);
        lineEdit_floor_amount->setObjectName(QString::fromUtf8("lineEdit_floor_amount"));
        lineEdit_floor_amount->setGeometry(QRect(130, 320, 91, 20));
        label_10 = new QLabel(objectOverview);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 320, 91, 17));
        lineEdit_year = new QLineEdit(objectOverview);
        lineEdit_year->setObjectName(QString::fromUtf8("lineEdit_year"));
        lineEdit_year->setGeometry(QRect(130, 290, 91, 20));
        label_11 = new QLabel(objectOverview);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 290, 101, 17));
        comboBox_client = new QComboBox(objectOverview);
        comboBox_client->setObjectName(QString::fromUtf8("comboBox_client"));
        comboBox_client->setGeometry(QRect(280, 360, 111, 20));
        label_client = new QLabel(objectOverview);
        label_client->setObjectName(QString::fromUtf8("label_client"));
        label_client->setGeometry(QRect(230, 363, 41, 17));
        pushButton_save = new QPushButton(objectOverview);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(20, 350, 201, 31));
        pushButton_deal = new QPushButton(objectOverview);
        pushButton_deal->setObjectName(QString::fromUtf8("pushButton_deal"));
        pushButton_deal->setGeometry(QRect(300, 290, 181, 31));
        lineEdit_type = new QLineEdit(objectOverview);
        lineEdit_type->setObjectName(QString::fromUtf8("lineEdit_type"));
        lineEdit_type->setGeometry(QRect(90, 30, 131, 24));
        checkBox_deal = new QCheckBox(objectOverview);
        checkBox_deal->setObjectName(QString::fromUtf8("checkBox_deal"));
        checkBox_deal->setGeometry(QRect(230, 290, 61, 31));
        checkBox_auth = new QCheckBox(objectOverview);
        checkBox_auth->setObjectName(QString::fromUtf8("checkBox_auth"));
        checkBox_auth->setGeometry(QRect(400, 363, 81, 17));
        pushButton_request = new QPushButton(objectOverview);
        pushButton_request->setObjectName(QString::fromUtf8("pushButton_request"));
        pushButton_request->setGeometry(QRect(300, 290, 181, 31));

        retranslateUi(objectOverview);

        QMetaObject::connectSlotsByName(objectOverview);
    } // setupUi

    void retranslateUi(QWidget *objectOverview)
    {
        objectOverview->setWindowTitle(QCoreApplication::translate("objectOverview", "Form", nullptr));
        label_deal->setText(QCoreApplication::translate("objectOverview", "\320\242\320\270\320\277 \321\201\320\264\320\265\320\273\320\272\320\270", nullptr));
        comboBox_deal->setPlaceholderText(QCoreApplication::translate("objectOverview", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("objectOverview", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("objectOverview", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        label_4->setText(QCoreApplication::translate("objectOverview", "\320\240\320\260\320\271\320\276\320\275", nullptr));
        label_5->setText(QCoreApplication::translate("objectOverview", "\320\242\320\270\320\277 \320\275\320\265\320\264\320\262\320\270\320\266\320\270\320\274\320\276\321\201\321\202\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("objectOverview", "ID", nullptr));
        label_7->setText(QCoreApplication::translate("objectOverview", "\320\246\320\265\320\275\320\260, USD", nullptr));
        label_rieltor->setText(QCoreApplication::translate("objectOverview", "\320\240\320\270\320\265\320\273\321\202\320\276\321\200", nullptr));
        comboBox_rieltor->setPlaceholderText(QCoreApplication::translate("objectOverview", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        label_9->setText(QCoreApplication::translate("objectOverview", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214, \320\2742", nullptr));
        lineEdit_floor_amount->setText(QString());
        label_10->setText(QCoreApplication::translate("objectOverview", "\320\232\320\276\320\273-\320\262\320\276 \320\272\320\276\320\274\320\275\320\260\321\202", nullptr));
        lineEdit_year->setText(QString());
        label_11->setText(QCoreApplication::translate("objectOverview", "\320\223\320\276\320\264 \321\201\321\202\321\200\320\276\320\270\321\202\320\265\320\273\321\214\321\201\321\202\320\262\320\260", nullptr));
        comboBox_client->setPlaceholderText(QCoreApplication::translate("objectOverview", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        label_client->setText(QCoreApplication::translate("objectOverview", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
        pushButton_save->setText(QCoreApplication::translate("objectOverview", "C\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        pushButton_deal->setText(QCoreApplication::translate("objectOverview", "\320\227\320\260\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \321\201\320\264\320\265\320\273\320\272\321\203", nullptr));
        checkBox_deal->setText(QCoreApplication::translate("objectOverview", "\320\241\320\264\320\265\320\273\320\272\320\260", nullptr));
        checkBox_auth->setText(QCoreApplication::translate("objectOverview", "\320\225\321\201\321\202\321\214 \320\262 \320\261\320\260\320\267\320\265", nullptr));
        pushButton_request->setText(QCoreApplication::translate("objectOverview", "\320\236\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\321\217\320\262\320\272\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class objectOverview: public Ui_objectOverview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTOVERVIEW_H
