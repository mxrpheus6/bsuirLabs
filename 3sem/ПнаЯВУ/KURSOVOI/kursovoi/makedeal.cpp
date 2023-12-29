#include "makedeal.h"
#include "ui_makedeal.h"

MakeDeal::MakeDeal(QWidget *parent, QWidget *parentOfParent, bool isRequested, QString propertyID, QString rieltorName, QString clientName) :
    QWidget(parent),
    ui(new Ui::MakeDeal)
{
    ui->setupUi(this);
    this->propertyID = propertyID.toInt();
    this->parent = parent;
    this->parentOfParent = parentOfParent;
    this->rieltorName = rieltorName;
    this->isRequested = isRequested;

    ui->lineEdit_clientID->setReadOnly(true);

    model = new QSqlTableModel();
    model->setTable(ACCOUNTS);
    model->select();
    model->sort(ID_COL, Qt::AscendingOrder);

    if (!clientName.isEmpty()) {
        ui->lineEdit_login->setReadOnly(true);
        ui->lineEdit_password->setReadOnly(true);

        QModelIndex index;
        QVariant data;

        int currentRow = findRowByField(clientName, NAME_COL);

        index = model->index(currentRow, ID_COL);
        data = model->data(index);
        ui->lineEdit_clientID->setText(data.toString());

        index = model->index(currentRow, NAME_COL);
        data = model->data(index);
        ui->lineEdit_name->setText(data.toString());

        index = model->index(currentRow, LOGIN_COL);
        data = model->data(index);
        ui->lineEdit_login->setText(data.toString());

        index = model->index(currentRow, PASSWORD_COL);
        data = model->data(index);
        ui->lineEdit_password->setText(data.toString());

        index = model->index(currentRow, PASSPORT_COL);
        data = model->data(index);
        ui->lineEdit_passport->setText(data.toString());

        index = model->index(currentRow, PHONE_COL);
        data = model->data(index);
        ui->lineEdit_phone->setText(data.toString());
    }
    else
        ui->lineEdit_clientID->setText(QString::number(generateID()));

}

MakeDeal::~MakeDeal()
{
    delete ui;

    delete model;
}

int MakeDeal::findRowByField(QString field, int column) {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < model->rowCount(); row++) {
           index = model->index(row, column);
           data = model->data(index).toString();
           if (data.toString() == field)
               return row;
    }
    return -1;
}

int MakeDeal::generateID() {
    QModelIndex index;
    QVariant data;
    int row = 1;

    for (row = 1; row <= model->rowCount(); row++) {
           index = model->index(row - 1, ID_COL);
           data = model->data(index);

           if (data.toInt() != row) {
               return row;
           }
    }
    return row;
}

void MakeDeal::removeRequest() {
    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(REQUESTS);
    tempModel->select();

    QModelIndex index;

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, ID_COL);
        if (tempModel->data(index).toInt() == propertyID) {
            tempModel->removeRow(row);
            tempModel->select();
            return;
        }
    }
    delete tempModel;
}

void MakeDeal::on_pushButton_deal_clicked()
{
    if (!checkEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    Client* client = new Client();
    try {
        client->setID(ui->lineEdit_clientID->text().toInt());
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

    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(DEALS);
    tempModel->select();

    int rowToAdd = tempModel->rowCount();
    tempModel->insertRow(rowToAdd);

    QModelIndex index;
    int rieltorRow = findRowByField(rieltorName, NAME_COL);
    index = model->index(rieltorRow, ID_COL);

    int rieltorID = model->data(index).toInt();
    index = tempModel->index(rowToAdd, ID_COL);
    tempModel->setData(index, propertyID);

    index = tempModel->index(rowToAdd, ID_RIELTOR);
    tempModel->setData(index, rieltorID);

    index = tempModel->index(rowToAdd, ID_CLIENT_DEAL);
    tempModel->setData(index, ui->lineEdit_clientID->text().toInt());

    int rowToUpdate = findRowByField(ui->lineEdit_clientID->text(), ID_COL);
    if (rowToUpdate == -1) {
        rowToUpdate = model->rowCount();
        model->insertRow(rowToUpdate);
    }

    index = model->index(rowToUpdate, ID_COL);
    model->setData(index, client->getID());

    index = model->index(rowToUpdate, NAME_COL);
    model->setData(index, client->getName());

    index = model->index(rowToUpdate, LOGIN_COL);
    model->setData(index, client->getLogin());

    index = model->index(rowToUpdate, PASSWORD_COL);
    model->setData(index, client->getPassword());

    index = model->index(rowToUpdate, PASSPORT_COL);
    model->setData(index, client->getPassport());

    index = model->index(rowToUpdate, PHONE_COL);
    model->setData(index, client->getPhone());

    index = model->index(rowToUpdate, ACCESS_COL);
    model->setData(index, client->getAccess());

    delete client;
    if (tempModel->submitAll() && model->submitAll()) {
        QMessageBox::information(this, "Успех", "Сделка совершена!");
        if (isRequested) {
            removeRequest();
        }
        parent->close();
        parentOfParent->close();
    }
    else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так...");
    }
}

bool MakeDeal::checkEmpty() {
    bool res = true;

    if (ui->lineEdit_name->text().isEmpty()) {
           ui->lineEdit_name->setStyleSheet("border: 1px solid red;");
           res = false;
    }

    if (ui->lineEdit_login->text().isEmpty()) {
           ui->lineEdit_login->setStyleSheet("border: 1px solid red;");
           res = false;
    }

    if (ui->lineEdit_password->text().isEmpty()) {
           ui->lineEdit_password->setStyleSheet("border: 1px solid red;");
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

void MakeDeal::on_lineEdit_name_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_name->setStyleSheet("");
}


void MakeDeal::on_lineEdit_login_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_login->setStyleSheet("");
}


void MakeDeal::on_lineEdit_password_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_password->setStyleSheet("");
}


void MakeDeal::on_lineEdit_passport_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_passport->setStyleSheet("");
}


void MakeDeal::on_lineEdit_phone_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_phone->setStyleSheet("");
}

