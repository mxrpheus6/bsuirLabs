#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define ACCOUNTS "Accounts"
#define DISTRICTS "Districts"
#define ESTATE "Estate"

#include <QMainWindow>
#include <QPixMap>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDialog>

#include "menudatawidget.h"
#include "realestatebase.h"

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

private:
    Ui::MainWindow *ui;
    QMainWindow *realtorWindow;
    QMainWindow *districtWindow;
    MenuDataWidget *mw;
    QSqlDatabase db;
    QSqlTableModel *model;
};
#endif // MAINWINDOW_H
