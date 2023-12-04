#ifndef MAKEDEAL_H
#define MAKEDEAL_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QDateTime>

#include "defines.h"
#include "client.h"

namespace Ui {
class MakeDeal;
}

class MakeDeal : public QWidget
{
    Q_OBJECT

public:
    explicit MakeDeal(QWidget *parent, QString properyID, QString rieltorName, QString clientName = "");
    ~MakeDeal();
    int findUserRow(QString user);
    int findUserRowByID(QString ID);
    int generateID();
    bool checkEmpty();

private slots:
    void on_pushButton_deal_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_login_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);

    void on_lineEdit_passport_textChanged(const QString &arg1);

    void on_lineEdit_phone_textChanged(const QString &arg1);

private:
    Ui::MakeDeal *ui;
    QWidget* parent;
    QSqlTableModel* model;
    QString rieltorName;
    int propertyID;
};

#endif // MAKEDEAL_H
