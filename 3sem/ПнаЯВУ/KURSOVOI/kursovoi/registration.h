#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlTableModel>

#include "client.h"
#include "defines.h"

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent);
    ~Registration();
    bool checkEmpty();
    int generateID();
    bool checkLoginTaken();

private slots:
    void on_pushButton_register_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_phone_textChanged(const QString &arg1);

    void on_lineEdit_login_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);

    void on_lineEdit_passport_textChanged(const QString &arg1);

private:
    Ui::Registration *ui;
    QWidget* parent;
    QSqlTableModel* model;
};

#endif // REGISTRATION_H
