/********************************************************************************
** Form generated from reading UI file 'menudatawidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUDATAWIDGET_H
#define UI_MENUDATAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuDataWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_del;
    QTableView *tableView_db;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MenuDataWidget)
    {
        if (MenuDataWidget->objectName().isEmpty())
            MenuDataWidget->setObjectName(QString::fromUtf8("MenuDataWidget"));
        MenuDataWidget->resize(400, 300);
        MenuDataWidget->setMinimumSize(QSize(400, 300));
        MenuDataWidget->setMaximumSize(QSize(400, 300));
        gridLayout = new QGridLayout(MenuDataWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_add = new QPushButton(MenuDataWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        gridLayout->addWidget(pushButton_add, 1, 1, 1, 1);

        pushButton_del = new QPushButton(MenuDataWidget);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));

        gridLayout->addWidget(pushButton_del, 1, 2, 1, 1);

        tableView_db = new QTableView(MenuDataWidget);
        tableView_db->setObjectName(QString::fromUtf8("tableView_db"));
        tableView_db->setMinimumSize(QSize(0, 0));
        tableView_db->setGridStyle(Qt::SolidLine);

        gridLayout->addWidget(tableView_db, 0, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 1);


        retranslateUi(MenuDataWidget);

        QMetaObject::connectSlotsByName(MenuDataWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuDataWidget)
    {
        MenuDataWidget->setWindowTitle(QCoreApplication::translate("MenuDataWidget", "Form", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MenuDataWidget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_del->setText(QCoreApplication::translate("MenuDataWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuDataWidget: public Ui_MenuDataWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUDATAWIDGET_H
