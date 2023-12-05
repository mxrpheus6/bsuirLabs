#ifndef MAKEDEAL_H
#define MAKEDEAL_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMessageBox>

#include "defines.h"
#include "client.h"

namespace Ui {
class MakeDeal;
}

class MakeDeal : public QWidget
{
    Q_OBJECT

public:
    explicit MakeDeal(QWidget *parent, QWidget *parentOfParent, bool isRequested, QString properyID, QString rieltorName, QString clientName = "");
    ~MakeDeal();
    void removeRequest();
    int findUserRow(QString user);
    int findUserRowByID(QString ID);
    int findID(QAbstractItemModel* model, int ID);
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
    QWidget* parentOfParent;
    QSqlTableModel* model;
    QString rieltorName;
    int propertyID;
    bool isRequested;
};

#endif // MAKEDEAL_H
