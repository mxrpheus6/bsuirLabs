#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QPixMap>


namespace Ui {
class Authorization;
}

class Authorization : public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

    bool getAuthorizationResult() const;
    void setAuthorizationResult(bool result);

signals:
    void authorizationSuccess();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Authorization *ui;
    bool authorizationResult = false;
    QSqlDatabase db;
};

#endif // AUTHORIZATION_H
