/********************************************************************************
** Form generated from reading UI file 'realestatebase.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALESTATEBASE_H
#define UI_REALESTATEBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealEstateBase
{
public:
    QTableView *tableView_estate;
    QCheckBox *checkBox_type;
    QComboBox *comboBox_type;
    QCheckBox *checkBox_district;
    QComboBox *comboBox_district;
    QCheckBox *checkBox_square;
    QComboBox *comboBox_floor_amount;
    QCheckBox *checkBox_price;
    QLineEdit *lineEdit_price_from;
    QLineEdit *lineEdit_price_to;
    QPushButton *pushButton_estate;
    QPushButton *pushButton_delete;
    QCheckBox *checkBox_floor_amount;
    QCheckBox *checkBox_year;
    QPushButton *pushButton_add;
    QLineEdit *lineEdit_year_to;
    QLineEdit *lineEdit_year_from;
    QLineEdit *lineEdit_square_to;
    QLineEdit *lineEdit_square_from;

    void setupUi(QWidget *RealEstateBase)
    {
        if (RealEstateBase->objectName().isEmpty())
            RealEstateBase->setObjectName(QString::fromUtf8("RealEstateBase"));
        RealEstateBase->resize(550, 450);
        RealEstateBase->setMinimumSize(QSize(550, 450));
        RealEstateBase->setMaximumSize(QSize(550, 450));
        tableView_estate = new QTableView(RealEstateBase);
        tableView_estate->setObjectName(QString::fromUtf8("tableView_estate"));
        tableView_estate->setGeometry(QRect(9, 9, 531, 281));
        checkBox_type = new QCheckBox(RealEstateBase);
        checkBox_type->setObjectName(QString::fromUtf8("checkBox_type"));
        checkBox_type->setGeometry(QRect(10, 300, 101, 22));
        comboBox_type = new QComboBox(RealEstateBase);
        comboBox_type->setObjectName(QString::fromUtf8("comboBox_type"));
        comboBox_type->setGeometry(QRect(10, 330, 101, 24));
        checkBox_district = new QCheckBox(RealEstateBase);
        checkBox_district->setObjectName(QString::fromUtf8("checkBox_district"));
        checkBox_district->setGeometry(QRect(130, 300, 59, 22));
        comboBox_district = new QComboBox(RealEstateBase);
        comboBox_district->setObjectName(QString::fromUtf8("comboBox_district"));
        comboBox_district->setGeometry(QRect(130, 330, 101, 24));
        checkBox_square = new QCheckBox(RealEstateBase);
        checkBox_square->setObjectName(QString::fromUtf8("checkBox_square"));
        checkBox_square->setGeometry(QRect(250, 300, 101, 22));
        comboBox_floor_amount = new QComboBox(RealEstateBase);
        comboBox_floor_amount->setObjectName(QString::fromUtf8("comboBox_floor_amount"));
        comboBox_floor_amount->setGeometry(QRect(10, 400, 101, 24));
        checkBox_price = new QCheckBox(RealEstateBase);
        checkBox_price->setObjectName(QString::fromUtf8("checkBox_price"));
        checkBox_price->setGeometry(QRect(250, 372, 81, 22));
        lineEdit_price_from = new QLineEdit(RealEstateBase);
        lineEdit_price_from->setObjectName(QString::fromUtf8("lineEdit_price_from"));
        lineEdit_price_from->setGeometry(QRect(250, 400, 41, 24));
        lineEdit_price_to = new QLineEdit(RealEstateBase);
        lineEdit_price_to->setObjectName(QString::fromUtf8("lineEdit_price_to"));
        lineEdit_price_to->setGeometry(QRect(300, 400, 41, 24));
        pushButton_estate = new QPushButton(RealEstateBase);
        pushButton_estate->setObjectName(QString::fromUtf8("pushButton_estate"));
        pushButton_estate->setGeometry(QRect(370, 300, 171, 61));
        pushButton_delete = new QPushButton(RealEstateBase);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(460, 370, 81, 55));
        checkBox_floor_amount = new QCheckBox(RealEstateBase);
        checkBox_floor_amount->setObjectName(QString::fromUtf8("checkBox_floor_amount"));
        checkBox_floor_amount->setGeometry(QRect(10, 370, 101, 22));
        checkBox_year = new QCheckBox(RealEstateBase);
        checkBox_year->setObjectName(QString::fromUtf8("checkBox_year"));
        checkBox_year->setGeometry(QRect(130, 370, 45, 22));
        pushButton_add = new QPushButton(RealEstateBase);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setGeometry(QRect(370, 370, 81, 55));
        lineEdit_year_to = new QLineEdit(RealEstateBase);
        lineEdit_year_to->setObjectName(QString::fromUtf8("lineEdit_year_to"));
        lineEdit_year_to->setGeometry(QRect(180, 400, 41, 24));
        lineEdit_year_from = new QLineEdit(RealEstateBase);
        lineEdit_year_from->setObjectName(QString::fromUtf8("lineEdit_year_from"));
        lineEdit_year_from->setGeometry(QRect(130, 400, 41, 24));
        lineEdit_square_to = new QLineEdit(RealEstateBase);
        lineEdit_square_to->setObjectName(QString::fromUtf8("lineEdit_square_to"));
        lineEdit_square_to->setGeometry(QRect(300, 330, 41, 24));
        lineEdit_square_from = new QLineEdit(RealEstateBase);
        lineEdit_square_from->setObjectName(QString::fromUtf8("lineEdit_square_from"));
        lineEdit_square_from->setGeometry(QRect(250, 330, 41, 24));

        retranslateUi(RealEstateBase);

        QMetaObject::connectSlotsByName(RealEstateBase);
    } // setupUi

    void retranslateUi(QWidget *RealEstateBase)
    {
        RealEstateBase->setWindowTitle(QCoreApplication::translate("RealEstateBase", "Form", nullptr));
        checkBox_type->setText(QCoreApplication::translate("RealEstateBase", "\320\242\320\270\320\277", nullptr));
        comboBox_type->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        checkBox_district->setText(QCoreApplication::translate("RealEstateBase", "\320\240\320\260\320\271\320\276\320\275", nullptr));
        comboBox_district->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        checkBox_square->setText(QCoreApplication::translate("RealEstateBase", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214, \320\2742", nullptr));
        comboBox_floor_amount->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265", nullptr));
        checkBox_price->setText(QCoreApplication::translate("RealEstateBase", "\320\246\320\265\320\275\320\260, USD", nullptr));
        lineEdit_price_from->setInputMask(QString());
        lineEdit_price_from->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\236\321\202", nullptr));
        lineEdit_price_to->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\224\320\276", nullptr));
        pushButton_estate->setText(QCoreApplication::translate("RealEstateBase", "\320\232\320\260\321\200\321\202\320\276\321\207\320\272\320\260 \320\276\320\261\321\212\320\265\320\272\321\202\320\260", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("RealEstateBase", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        checkBox_floor_amount->setText(QCoreApplication::translate("RealEstateBase", "\320\232\320\276\320\273-\320\262\320\276 \320\272\320\276\320\274\320\275\320\260\321\202", nullptr));
        checkBox_year->setText(QCoreApplication::translate("RealEstateBase", "\320\223\320\276\320\264", nullptr));
        pushButton_add->setText(QCoreApplication::translate("RealEstateBase", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        lineEdit_year_to->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\224\320\276", nullptr));
        lineEdit_year_from->setInputMask(QString());
        lineEdit_year_from->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\236\321\202", nullptr));
        lineEdit_square_to->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\224\320\276", nullptr));
        lineEdit_square_from->setInputMask(QString());
        lineEdit_square_from->setPlaceholderText(QCoreApplication::translate("RealEstateBase", "\320\236\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealEstateBase: public Ui_RealEstateBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALESTATEBASE_H
