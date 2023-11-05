/********************************************************************************
** Form generated from reading UI file 'realtorwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTORWIDGET_H
#define UI_REALTORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealtorWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_add;
    QPushButton *pushButton_delete;

    void setupUi(QWidget *RealtorWidget)
    {
        if (RealtorWidget->objectName().isEmpty())
            RealtorWidget->setObjectName(QString::fromUtf8("RealtorWidget"));
        RealtorWidget->setWindowModality(Qt::NonModal);
        RealtorWidget->resize(400, 300);
        RealtorWidget->setMinimumSize(QSize(400, 300));
        RealtorWidget->setMaximumSize(QSize(400, 300));
        gridLayout = new QGridLayout(RealtorWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableView = new QTableView(RealtorWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMinimumSize(QSize(0, 0));
        tableView->setGridStyle(Qt::SolidLine);

        verticalLayout_3->addWidget(tableView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_add = new QPushButton(RealtorWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(pushButton_add);

        pushButton_delete = new QPushButton(RealtorWidget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(pushButton_delete);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(RealtorWidget);

        QMetaObject::connectSlotsByName(RealtorWidget);
    } // setupUi

    void retranslateUi(QWidget *RealtorWidget)
    {
        RealtorWidget->setWindowTitle(QCoreApplication::translate("RealtorWidget", "\320\240\320\270\320\265\320\273\321\202\320\276\321\200\321\213", nullptr));
        pushButton_add->setText(QCoreApplication::translate("RealtorWidget", "+", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("RealtorWidget", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealtorWidget: public Ui_RealtorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTORWIDGET_H
