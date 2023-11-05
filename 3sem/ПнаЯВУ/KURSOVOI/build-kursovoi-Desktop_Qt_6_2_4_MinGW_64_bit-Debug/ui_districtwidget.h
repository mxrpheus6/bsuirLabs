/********************************************************************************
** Form generated from reading UI file 'districtwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTRICTWIDGET_H
#define UI_DISTRICTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DistrictWidget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_add;
    QPushButton *pushButton_delete;

    void setupUi(QWidget *DistrictWidget)
    {
        if (DistrictWidget->objectName().isEmpty())
            DistrictWidget->setObjectName(QString::fromUtf8("DistrictWidget"));
        DistrictWidget->resize(400, 300);
        DistrictWidget->setMinimumSize(QSize(400, 300));
        DistrictWidget->setMaximumSize(QSize(400, 300));
        layoutWidget = new QWidget(DistrictWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 281));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(0, 0));
        tableView->setGridStyle(Qt::SolidLine);

        verticalLayout_3->addWidget(tableView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_add = new QPushButton(layoutWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(pushButton_add);

        pushButton_delete = new QPushButton(layoutWidget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(pushButton_delete);


        verticalLayout_3->addLayout(horizontalLayout_3);


        retranslateUi(DistrictWidget);

        QMetaObject::connectSlotsByName(DistrictWidget);
    } // setupUi

    void retranslateUi(QWidget *DistrictWidget)
    {
        DistrictWidget->setWindowTitle(QCoreApplication::translate("DistrictWidget", "\320\240\320\260\320\271\320\276\320\275\321\213", nullptr));
        pushButton_add->setText(QCoreApplication::translate("DistrictWidget", "+", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("DistrictWidget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DistrictWidget: public Ui_DistrictWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTRICTWIDGET_H
