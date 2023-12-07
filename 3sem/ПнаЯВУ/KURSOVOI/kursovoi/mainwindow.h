#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QApplication>
#include <QMainWindow>
#include <QPixMap>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDialog>

#include "menudatawidget.h"
#include "realestatebase.h"
#include "defines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_realtors_triggered();

    void on_action_districts_triggered();

    void on_pushButton_real_estate_base_clicked();

    void on_pushButton_real_estate_applications_clicked();

    void on_pushButton_deals_clicked();

public slots:
    void handleAuthorizationSuccessWithAccess(QString access, int ID);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;

    QString access;
    int userID;
};
#endif // MAINWINDOW_H
