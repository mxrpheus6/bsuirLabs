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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealEstateBase
{
public:

    void setupUi(QWidget *RealEstateBase)
    {
        if (RealEstateBase->objectName().isEmpty())
            RealEstateBase->setObjectName(QString::fromUtf8("RealEstateBase"));
        RealEstateBase->resize(550, 450);
        RealEstateBase->setMinimumSize(QSize(550, 450));
        RealEstateBase->setMaximumSize(QSize(550, 450));

        retranslateUi(RealEstateBase);

        QMetaObject::connectSlotsByName(RealEstateBase);
    } // setupUi

    void retranslateUi(QWidget *RealEstateBase)
    {
        RealEstateBase->setWindowTitle(QCoreApplication::translate("RealEstateBase", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealEstateBase: public Ui_RealEstateBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALESTATEBASE_H
