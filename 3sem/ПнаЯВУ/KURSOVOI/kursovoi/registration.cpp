#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->parent = parent;

    ui->lineEdit_ID->setReadOnly(true);

    model = new QSqlTableModel();
    model->setTable(ACCOUNTS);
    model->select();

    ui->lineEdit_ID->setText(QString::number(generateID()));
}

Registration::~Registration()
{
    delete ui;

    delete model;
}

int Registration::generateID() {
    QModelIndex index;
    QVariant data;
    int row = 1;
    model->sort(ID_COL, Qt::AscendingOrder);

    for (row = 1; row <= model->rowCount(); row++) {
        index = model->index(row - 1, ID_COL);
        data = model->data(index);

        if (data.toInt() != row) {
            return row;
        }
    }
    return row;
}

bool Registration::checkEmpty() {
    bool res = true;

    if (ui->lineEdit_login->text().isEmpty()) {
        ui->lineEdit_login->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_password->text().isEmpty()) {
        ui->lineEdit_password->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_name->text().isEmpty()) {
        ui->lineEdit_name->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_passport->text().isEmpty()) {
        ui->lineEdit_passport->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_phone->text().isEmpty()) {
        ui->lineEdit_phone->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    return res;
}

bool Registration::checkLoginTaken() {
    QModelIndex index;
    for (int row = 0; row < model->rowCount(); row++) {
        index = model->index(row, LOGIN_COL);   //столбец логина
        if (model->data(index).toString() == ui->lineEdit_login->text())
            return false;
    }
    return true;
}

void Registration::on_pushButton_register_clicked()
{
    if (!checkEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    Client* client = new Client();
    try {
        client->setID(ui->lineEdit_ID->text().toInt());
        client->setName(ui->lineEdit_name->text());
        client->setLogin(ui->lineEdit_login->text());
        client->setPassword(ui->lineEdit_password->text());
        client->setPassport(ui->lineEdit_passport->text());
        client->setPhone(ui->lineEdit_phone->text());
    }
    catch (QString errorMessage) {
        QMessageBox::warning(this, "Предупреждение", errorMessage);
        delete client;
        return;
    }

    if (!checkLoginTaken()) {
        QMessageBox::warning(this, "Предупреждение", "Ваш логин уже занят!");
        return;
    }

    QModelIndex index;
    int rowToAdd = model->rowCount();
    model->insertRow(rowToAdd);

    index = model->index(rowToAdd, ID_COL);
    model->setData(index, client->getID());

    index = model->index(rowToAdd, NAME_COL);
    model->setData(index, client->getName());

    index = model->index(rowToAdd, LOGIN_COL);
    model->setData(index, client->getLogin());

    index = model->index(rowToAdd, PASSWORD_COL);
    model->setData(index, client->getPassword());

    index = model->index(rowToAdd, PASSPORT_COL);
    model->setData(index, client->getPassport());

    index = model->index(rowToAdd, PHONE_COL);
    model->setData(index, client->getPhone());

    index = model->index(rowToAdd, ACCESS_COL);
    model->setData(index, client->getAccess());

    if (model->submitAll()) {
        QMessageBox::information(this, "Успех", "Вы зарегистрированы!");
        parent->close();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так...");
    }

    delete client;
}


void Registration::on_lineEdit_name_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_name->setStyleSheet("");
}


void Registration::on_lineEdit_phone_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_phone->setStyleSheet("");
}


void Registration::on_lineEdit_login_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_login->setStyleSheet("");
}


void Registration::on_lineEdit_password_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_password->setStyleSheet("");
}


void Registration::on_lineEdit_passport_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_passport->setStyleSheet("");
}
