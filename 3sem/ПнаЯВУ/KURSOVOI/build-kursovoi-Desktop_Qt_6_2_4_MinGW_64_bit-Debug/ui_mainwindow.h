/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_realtors;
    QAction *action_districts;
    QWidget *centralwidget;
    QLabel *label_banner;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_real_estate_base;
    QPushButton *pushButton_real_estate_applications;
    QPushButton *pushButton_deals;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(640, 480);
        MainWindow->setMinimumSize(QSize(640, 480));
        MainWindow->setMaximumSize(QSize(640, 480));
        MainWindow->setTabShape(QTabWidget::Rounded);
        action_realtors = new QAction(MainWindow);
        action_realtors->setObjectName(QString::fromUtf8("action_realtors"));
        action_realtors->setCheckable(false);
        action_districts = new QAction(MainWindow);
        action_districts->setObjectName(QString::fromUtf8("action_districts"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_banner = new QLabel(centralwidget);
        label_banner->setObjectName(QString::fromUtf8("label_banner"));
        label_banner->setGeometry(QRect(9, 9, 622, 201));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 230, 621, 201));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_real_estate_base = new QPushButton(verticalLayoutWidget);
        pushButton_real_estate_base->setObjectName(QString::fromUtf8("pushButton_real_estate_base"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_real_estate_base->sizePolicy().hasHeightForWidth());
        pushButton_real_estate_base->setSizePolicy(sizePolicy);
        pushButton_real_estate_base->setMinimumSize(QSize(0, 70));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 147, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pushButton_real_estate_base->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        pushButton_real_estate_base->setFont(font);

        horizontalLayout_4->addWidget(pushButton_real_estate_base);

        pushButton_real_estate_applications = new QPushButton(verticalLayoutWidget);
        pushButton_real_estate_applications->setObjectName(QString::fromUtf8("pushButton_real_estate_applications"));
        sizePolicy.setHeightForWidth(pushButton_real_estate_applications->sizePolicy().hasHeightForWidth());
        pushButton_real_estate_applications->setSizePolicy(sizePolicy);
        pushButton_real_estate_applications->setMinimumSize(QSize(0, 70));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pushButton_real_estate_applications->setPalette(palette1);
        pushButton_real_estate_applications->setFont(font);

        horizontalLayout_4->addWidget(pushButton_real_estate_applications);


        verticalLayout_2->addLayout(horizontalLayout_4);

        pushButton_deals = new QPushButton(verticalLayoutWidget);
        pushButton_deals->setObjectName(QString::fromUtf8("pushButton_deals"));
        pushButton_deals->setMinimumSize(QSize(0, 90));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pushButton_deals->setPalette(palette2);
        pushButton_deals->setFont(font);

        verticalLayout_2->addWidget(pushButton_deals);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setEnabled(true);
        menu->setTearOffEnabled(false);
        menu->setSeparatorsCollapsible(false);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_realtors);
        menu->addAction(action_districts);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\276\320\275\320\275\320\276-\321\201\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\260\320\263\320\265\320\275\321\201\321\202\320\262\320\260 \320\275\320\265\320\264\320\262\320\270\320\266\320\270\320\274\320\276\321\201\321\202\320\270", nullptr));
        action_realtors->setText(QCoreApplication::translate("MainWindow", "\320\240\320\270\320\265\320\273\321\202\320\276\321\200\321\213", nullptr));
        action_districts->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\271\320\276\320\275\321\213", nullptr));
        label_banner->setText(QString());
        pushButton_real_estate_base->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260 \320\275\320\265\320\264\320\262\320\270\320\266\320\270\320\274\320\276\321\201\321\202\320\270", nullptr));
        pushButton_real_estate_applications->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270 \320\275\320\260 \321\201\320\264\320\265\320\273\320\272\321\203", nullptr));
        pushButton_deals->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \321\201\320\264\320\265\320\273\320\272\320\270", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
