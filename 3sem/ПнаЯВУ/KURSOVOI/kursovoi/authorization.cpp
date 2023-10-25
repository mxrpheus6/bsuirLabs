#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

    QPixmap pix("./img/auth_pic.png");
    ui->label_auth_pic->setPixmap(pix.scaled(152, 78, Qt::KeepAspectRatio));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db/real_estate.db");
    if (db.open()) {
        qDebug("db connected");
    }
    else {
        qDebug("db isnt connected");
    }
}

Authorization::~Authorization()
{
    db.close();
    delete ui;
}

bool Authorization::getAuthorizationResult() const {
    return authorizationResult;
}

void Authorization::setAuthorizationResult(bool result) {
    authorizationResult = result;
}

void Authorization::on_pushButton_login_clicked()
{
    if (!db.isOpen()) {
        qDebug("Failed to connect to db after click");
        return;
    }

    QString login = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    bool authenticated;
    QSqlQuery query;
    query.prepare("SELECT * FROM Accounts WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        authenticated = false;

        while (query.next()) {
            authenticated = true;
        }

        if (authenticated) {
            QMessageBox::information(this, "Вход", "Успешно!");
            emit authorizationSuccess();
        }
        else {
            QMessageBox::warning(this, "Вход", "Неверный логин и\или пароль!");
            ui->lineEdit_password->clear();
        }
    }
}
