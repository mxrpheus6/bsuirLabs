/********************************************************************************
** Form generated from reading UI file 'realtors.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTORS_H
#define UI_REALTORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DB
{
public:

    void setupUi(QWidget *DB)
    {
        if (DB->objectName().isEmpty())
            DB->setObjectName(QString::fromUtf8("DB"));
        DB->resize(400, 300);

        retranslateUi(DB);

        QMetaObject::connectSlotsByName(DB);
    } // setupUi

    void retranslateUi(QWidget *DB)
    {
        DB->setWindowTitle(QCoreApplication::translate("DB", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DB: public Ui_DB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTORS_H
