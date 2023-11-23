#include "objectoverview.h"
#include "ui_objectoverview.h"

objectOverview::objectOverview(QWidget *parent, QSqlTableModel* model, QString tableName, int objectRow) :
    QWidget(parent),
    ui(new Ui::objectOverview)
{
    ui->setupUi(this);

    QModelIndex index;
    QVariant data;

    QSqlTableModel* tempModel = new QSqlTableModel(this);
    tempModel->setTable("Districts");
    tempModel->select();

    //установка combobox для района
    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 0);
        data = tempModel->data(index);

        ui->comboBox_district->addItem(data.toString());
        index = model->index(objectRow, DISTRICT_COL);
        if (data.toString() == model->data(index)) {
            ui->comboBox_district->setCurrentIndex(row);
        }
    }

    tempModel->setTable("Accounts");
    tempModel->select();

    //установка combobox для сделок
    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 3);
        data = tempModel->data(index);

        if (data.toString() == "rieltor") {
            index = tempModel->index(row, 0);
            ui->comboBox_rieltor->addItem(tempModel->data(index).toString());
        }
    }

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 3);
        data = tempModel->data(index);

        if (data.toString() == "client") {
            index = tempModel->index(row, 0);
            ui->comboBox_client->addItem(tempModel->data(index).toString());
        }
    }

    QString dealsArr[] = DEALS_ARR;
    int dealsSize = sizeof(dealsArr) / sizeof(dealsArr[0]);
    for (int i = 0; i < dealsSize; i++) {
        ui->comboBox_deal->addItem(dealsArr[i]);

        index = model->index(objectRow, DEAL_TYPE_COL);
        data = model->data(index);
        if (data.toString() == dealsArr[i]) {
            ui->comboBox_deal->setCurrentIndex(i);
        }
    }

    //устанавливаем lineEdit выбранного объекта
    index = model->index(objectRow, PROPERTY_TYPE_COL);
    data = model->data(index);
    ui->lineEdit_type->setText(data.toString());


    index = model->index(objectRow, DESCRIPTION_COL);
    data = model->data(index);
    ui->plainTextEdit_description->setPlainText(data.toString());

    index = model->index(objectRow, ADDRESS_COL);
    data = model->data(index);
    ui->lineEdit_address->setText(data.toString());

    index = model->index(objectRow, SQUARE_COL);
    data = model->data(index);
    ui->lineEdit_square->setText(data.toString());

    index = model->index(objectRow, FLOOR_AMOUNT_COL);
    data = model->data(index);
    ui->lineEdit_floor_amount->setText(data.toString());

    index = model->index(objectRow, YEAR_COL);
    data = model->data(index);
    ui->lineEdit_year->setText(data.toString());

    index = model->index(objectRow, ID_COL);
    data = model->data(index);
    ui->lineEdit_ID->setText(data.toString());

    index = model->index(objectRow, PRICE_COL);
    data = model->data(index);
    ui->lineEdit_price->setText(data.toString());


    //отключение кнопки
    ui->lineEdit_ID->setEnabled(false);
    ui->lineEdit_type->setEnabled(false);
    ui->pushButton_deal->setEnabled(false);
    ui->comboBox_deal->setEnabled(false);
    ui->comboBox_rieltor->setEnabled(false);
    ui->comboBox_client->setEnabled(false);


    QDoubleValidator *doubleValidator = new QDoubleValidator();
    ui->lineEdit_square->setValidator(doubleValidator);

    extendedModel = new QSqlTableModel(this);
    extendedModel->setTable(tableName);
    extendedModel->select();

    QStandardItemModel *itemModel = new QStandardItemModel(0, 2);

    //QSqlRecord record = extendedModel->record(0);

    //for (int i = 0; i < record.count() - 1; i++) {
        // Получаем имя переменной (название поля)
     //   QString variableName = record.fieldName(i + 1);

        // Создаем элемент для первого столбца (имена переменных)
     //   QStandardItem *variableItem = new QStandardItem(variableName);

        // Добавляем элемент в модель
    //    itemModel->setItem(i, 0, variableItem);
    //}

    fillTableHeaders(itemModel, tableName);

    int rowOfObject = findID();

    for (int i = 0; i < itemModel->rowCount(); i++) {
        // Получаем значение переменной
        QModelIndex index = extendedModel->index(rowOfObject, i + 1);
        QVariant data = extendedModel->data(index);

        QStandardItem *valueItem = new QStandardItem(data.toString());

        // Добавляем элемент в модель
        itemModel->setItem(i, 1, valueItem);
    }


    itemModel->setHeaderData(0, Qt::Horizontal, "Характеристика");
    itemModel->setHeaderData(1, Qt::Horizontal, "Значение");

    //fillTableHeaders(itemModel);

    ui->tableView_extended->setModel(itemModel);
    ui->tableView_extended->verticalHeader()->setVisible(false);
    ui->tableView_extended->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

objectOverview::~objectOverview()
{
    delete ui;
}


void objectOverview::on_checkBox_deal_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->pushButton_deal->setEnabled(true);
        ui->comboBox_deal->setEnabled(true);
        ui->comboBox_rieltor->setEnabled(true);
        ui->comboBox_client->setEnabled(true);
    }
    else {
        ui->pushButton_deal->setEnabled(false);
        ui->comboBox_deal->setEnabled(false);
        ui->comboBox_rieltor->setEnabled(false);
        ui->comboBox_client->setEnabled(false);

        ui->comboBox_rieltor->setCurrentIndex(-1);
        ui->comboBox_client->setCurrentIndex(-1);
    }
}

int objectOverview::findID() {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < extendedModel->rowCount(); row++) {
        index = extendedModel->index(row, 0);
        data = extendedModel->data(index).toString();
        if (data.toString() == ui->lineEdit_ID->text())
            return row;
    }
    return -1;
}

void objectOverview::fillTableHeaders(QStandardItemModel* model, QString tableName) {
    //QString fields[];
    QString fields[20];
    int sizeOfVect = 0;
    if (tableName == "Apartment") {
        sizeOfVect = fields_apartment.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_apartment[i];
        }
    }
    else if (tableName == "House") {
        sizeOfVect = fields_house.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_house[i];
        }
    }
    else if (tableName == "Office") {
        sizeOfVect = fields_office.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_office[i];
        }
    }
    else
        return;

    QModelIndex index;
    QStandardItem* valueItem;
    //int sizeOfArr = sizeof(fields) / sizeof(fields[0]);

    // Добавляем элемент в модель
    for (int i = 0; i < sizeOfVect; i++) {
        valueItem = new QStandardItem(fields[i]);
        model->setItem(i, 0, valueItem);

        index = model->index(i, 0);
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
    }
}
