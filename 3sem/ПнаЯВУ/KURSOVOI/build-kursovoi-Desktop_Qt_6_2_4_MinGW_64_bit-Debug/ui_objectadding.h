/********************************************************************************
** Form generated from reading UI file 'objectadding.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTADDING_H
#define UI_OBJECTADDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_objectAdding
{
public:
    QLabel *label;
    QLineEdit *lineEdit_ID;
    QLabel *label_2;
    QComboBox *comboBox_type;
    QComboBox *comboBox_deal;
    QLabel *label_3;
    QLabel *label_4;
    QPlainTextEdit *plainTextEdit_description;
    QComboBox *comboBox_district;
    QLabel *label_5;
    QLineEdit *lineEdit_address;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_square;
    QLabel *label_8;
    QLineEdit *lineEdit_floor_amount;
    QLabel *label_9;
    QLineEdit *lineEdit_price;
    QLabel *label_10;
    QLineEdit *lineEdit_year;
    QTableView *tableView;
    QPushButton *pushButton_save;

    void setupUi(QWidget *objectAdding)
    {
        if (objectAdding->objectName().isEmpty())
            objectAdding->setObjectName(QString::fromUtf8("objectAdding"));
        objectAdding->resize(300, 500);
        label = new QLabel(objectAdding);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 16, 16));
        lineEdit_ID = new QLineEdit(objectAdding);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(10, 30, 41, 24));
        label_2 = new QLabel(objectAdding);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 10, 111, 16));
        comboBox_type = new QComboBox(objectAdding);
        comboBox_type->setObjectName(QString::fromUtf8("comboBox_type"));
        comboBox_type->setGeometry(QRect(60, 30, 111, 24));
        comboBox_deal = new QComboBox(objectAdding);
        comboBox_deal->setObjectName(QString::fromUtf8("comboBox_deal"));
        comboBox_deal->setGeometry(QRect(180, 30, 111, 24));
        label_3 = new QLabel(objectAdding);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(180, 10, 71, 16));
        label_4 = new QLabel(objectAdding);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 61, 16));
        plainTextEdit_description = new QPlainTextEdit(objectAdding);
        plainTextEdit_description->setObjectName(QString::fromUtf8("plainTextEdit_description"));
        plainTextEdit_description->setGeometry(QRect(10, 80, 281, 70));
        comboBox_district = new QComboBox(objectAdding);
        comboBox_district->setObjectName(QString::fromUtf8("comboBox_district"));
        comboBox_district->setGeometry(QRect(10, 180, 131, 24));
        label_5 = new QLabel(objectAdding);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 41, 16));
        lineEdit_address = new QLineEdit(objectAdding);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));
        lineEdit_address->setGeometry(QRect(160, 180, 131, 24));
        label_6 = new QLabel(objectAdding);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(161, 160, 41, 16));
        label_7 = new QLabel(objectAdding);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 220, 81, 16));
        lineEdit_square = new QLineEdit(objectAdding);
        lineEdit_square->setObjectName(QString::fromUtf8("lineEdit_square"));
        lineEdit_square->setGeometry(QRect(10, 240, 81, 24));
        label_8 = new QLabel(objectAdding);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(210, 220, 81, 16));
        lineEdit_floor_amount = new QLineEdit(objectAdding);
        lineEdit_floor_amount->setObjectName(QString::fromUtf8("lineEdit_floor_amount"));
        lineEdit_floor_amount->setGeometry(QRect(210, 240, 81, 24));
        label_9 = new QLabel(objectAdding);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(12, 445, 81, 16));
        lineEdit_price = new QLineEdit(objectAdding);
        lineEdit_price->setObjectName(QString::fromUtf8("lineEdit_price"));
        lineEdit_price->setGeometry(QRect(10, 465, 81, 24));
        label_10 = new QLabel(objectAdding);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(110, 220, 91, 16));
        lineEdit_year = new QLineEdit(objectAdding);
        lineEdit_year->setObjectName(QString::fromUtf8("lineEdit_year"));
        lineEdit_year->setGeometry(QRect(110, 240, 81, 24));
        tableView = new QTableView(objectAdding);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 270, 281, 161));
        pushButton_save = new QPushButton(objectAdding);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(110, 445, 181, 46));

        retranslateUi(objectAdding);

        QMetaObject::connectSlotsByName(objectAdding);
    } // setupUi

    void retranslateUi(QWidget *objectAdding)
    {
        objectAdding->setWindowTitle(QCoreApplication::translate("objectAdding", "Form", nullptr));
        label->setText(QCoreApplication::translate("objectAdding", "ID", nullptr));
        label_2->setText(QCoreApplication::translate("objectAdding", "\320\242\320\270\320\277 \320\275\320\265\320\264\320\262\320\270\320\266\320\270\320\274\320\276\321\201\321\202\320\270", nullptr));
        comboBox_type->setPlaceholderText(QCoreApplication::translate("objectAdding", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        comboBox_deal->setPlaceholderText(QCoreApplication::translate("objectAdding", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        label_3->setText(QCoreApplication::translate("objectAdding", "\320\242\320\270\320\277 \321\201\320\264\320\265\320\273\320\272\320\270", nullptr));
        label_4->setText(QCoreApplication::translate("objectAdding", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        comboBox_district->setPlaceholderText(QCoreApplication::translate("objectAdding", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        label_5->setText(QCoreApplication::translate("objectAdding", "\320\240\320\260\320\271\320\276\320\275", nullptr));
        label_6->setText(QCoreApplication::translate("objectAdding", "\320\220\320\264\321\200\320\265\321\201", nullptr));
        label_7->setText(QCoreApplication::translate("objectAdding", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214, \320\2742", nullptr));
        label_8->setText(QCoreApplication::translate("objectAdding", "\320\232\320\276\320\273-\320\262\320\276 \320\272\320\276\320\274\320\275\320\260\321\202", nullptr));
        label_9->setText(QCoreApplication::translate("objectAdding", "\320\246\320\265\320\275\320\260, USD", nullptr));
        label_10->setText(QCoreApplication::translate("objectAdding", "\320\223\320\276\320\264 \320\277\320\276\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        pushButton_save->setText(QCoreApplication::translate("objectAdding", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class objectAdding: public Ui_objectAdding {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTADDING_H
