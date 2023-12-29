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
    delete ui;
}

void Authorization::on_pushButton_login_clicked()
{
    if (!db.isOpen()) {
        qDebug("Failed to connect to db after click");
        return;
    }

    QString login = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    bool authenticated = false;
    QSqlQuery query;
    query.prepare("SELECT * FROM Accounts WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QString access = query.value("access").toString();
            int ID = query.value("id").toInt();
            QMessageBox::information(this, "Вход", "Успешно!");
            emit authorizationSuccess(access, ID);
            return;
        }
    }

    if (!authenticated) {
        QMessageBox::warning(this, "Вход", "Неверный логин и\\или пароль!");
        ui->lineEditPassword->clear();
    }
}

void Authorization::on_pushButton_register_clicked()
{
    QDialog* dialog = new QDialog(this);
    Registration* reg = new Registration(dialog);
    dialog->setModal(true);
    dialog->setWindowTitle("Регистрация");
    dialog->setFixedSize(360, 240);
    reg->setParent(dialog);
    reg->show();

    dialog->exec();

    delete reg;
}

