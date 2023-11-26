#include "objectoverview.h"
#include "ui_objectoverview.h"

objectOverview::objectOverview(QWidget *parent, QSqlTableModel* originalModel, QAbstractItemModel* resModel, QString tableName, int objectRow) :
    QWidget(parent),
    ui(new Ui::objectOverview)
{
    ui->setupUi(this);

    QModelIndex index;
    QVariant data;

    model = originalModel;

    QSqlTableModel* tempModel = new QSqlTableModel(this);
    tempModel->setTable("Districts");
    tempModel->select();

    //установка combobox для района
    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 0);
        data = tempModel->data(index);

        ui->comboBox_district->addItem(data.toString());
        index = resModel->index(objectRow, DISTRICT_COL);
        if (data.toString() == resModel->data(index)) {
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

        index = resModel->index(objectRow, DEAL_TYPE_COL);
        data = resModel->data(index);
        if (data.toString() == dealsArr[i]) {
            ui->comboBox_deal->setCurrentIndex(i);
        }
    }

    //устанавливаем lineEdit выбранного объекта
    index = resModel->index(objectRow, PROPERTY_TYPE_COL);
    data = resModel->data(index);
    ui->lineEdit_type->setText(data.toString());


    index = resModel->index(objectRow, DESCRIPTION_COL);
    data = resModel->data(index);
    ui->plainTextEdit_description->setPlainText(data.toString());

    index = resModel->index(objectRow, ADDRESS_COL);
    data = resModel->data(index);
    ui->lineEdit_address->setText(data.toString());

    index = resModel->index(objectRow, SQUARE_COL);
    data = resModel->data(index);
    ui->lineEdit_square->setText(data.toString());

    index = resModel->index(objectRow, FLOOR_AMOUNT_COL);
    data = resModel->data(index);
    ui->lineEdit_floor_amount->setText(data.toString());

    index = resModel->index(objectRow, YEAR_COL);
    data = resModel->data(index);
    ui->lineEdit_year->setText(data.toString());

    index = resModel->index(objectRow, ID_COL);
    data = resModel->data(index);
    ui->lineEdit_ID->setText(data.toString());

    index = resModel->index(objectRow, PRICE_COL);
    data = resModel->data(index);
    ui->lineEdit_price->setText(data.toString());


    //отключение кнопки
    ui->lineEdit_ID->setEnabled(false);
    ui->lineEdit_type->setEnabled(false);
    ui->pushButton_deal->setEnabled(false);
    ui->comboBox_rieltor->setEnabled(false);
    ui->comboBox_client->setEnabled(false);


    QDoubleValidator *doubleValidator = new QDoubleValidator();
    QIntValidator *intValidator = new QIntValidator();

    ui->lineEdit_price->setValidator(doubleValidator);
    ui->lineEdit_square->setValidator(doubleValidator);
    ui->lineEdit_year->setValidator(intValidator);
    ui->lineEdit_floor_amount->setValidator(intValidator);

    extendedModel = new QSqlTableModel(this);
    extendedModel->setTable(tableName);
    extendedModel->select();

    itemModel = new QStandardItemModel(0, 2);

    fillTableHeaders(itemModel, tableName);

    int rowOfObject = findID(extendedModel);

    for (int i = 0; i < itemModel->rowCount(); i++) {
        QModelIndex index = extendedModel->index(rowOfObject, i + 1);
        QVariant data = extendedModel->data(index);

        QStandardItem *valueItem = new QStandardItem(data.toString());

        itemModel->setItem(i, 1, valueItem);
    }


    itemModel->setHeaderData(0, Qt::Horizontal, "Характеристика");
    itemModel->setHeaderData(1, Qt::Horizontal, "Значение");


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
        ui->comboBox_rieltor->setEnabled(true);
        ui->comboBox_client->setEnabled(true);
    }
    else {
        ui->pushButton_deal->setEnabled(false);
        ui->comboBox_rieltor->setEnabled(false);
        ui->comboBox_client->setEnabled(false);

        ui->comboBox_rieltor->setCurrentIndex(-1);
        ui->comboBox_client->setCurrentIndex(-1);
    }
}

int objectOverview::findID(QAbstractItemModel* model) {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < model->rowCount(); row++) {
        index = model->index(row, 0);
        data = model->data(index).toString();
        if (data.toString() == ui->lineEdit_ID->text())
            return row;
    }
    return -1;
}

void objectOverview::fillTableHeaders(QStandardItemModel* model, QString tableName) {
    QString fields[9];
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

    for (int i = 0; i < sizeOfVect; i++) {
        valueItem = new QStandardItem(fields[i]);
        model->setItem(i, 0, valueItem);

        index = model->index(i, 0);
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
    }
}

void objectOverview::on_pushButton_save_clicked()
{
    QModelIndex index;
    int rowToUpdate = findID(model);

    index = model->index(rowToUpdate, DESCRIPTION_COL);
    model->setData(index, ui->plainTextEdit_description->toPlainText());

    index = model->index(rowToUpdate, DISTRICT_COL);
    model->setData(index, ui->comboBox_district->currentText());

    index = model->index(rowToUpdate, ADDRESS_COL);
    model->setData(index, ui->lineEdit_address->text());

    index = model->index(rowToUpdate, PRICE_COL);
    model->setData(index, ui->lineEdit_price->text());

    index = model->index(rowToUpdate, SQUARE_COL);
    model->setData(index, ui->lineEdit_square->text());

    index = model->index(rowToUpdate, YEAR_COL);
    model->setData(index, ui->lineEdit_year->text());

    index = model->index(rowToUpdate, FLOOR_AMOUNT_COL);
    model->setData(index, ui->lineEdit_floor_amount->text());

    index = model->index(rowToUpdate, DEAL_TYPE_COL);
    model->setData(index, ui->comboBox_deal->currentText());

    rowToUpdate = findID(extendedModel);

    if (ui->lineEdit_type->text() == APARTMENT)
        updateExtended(fields_apartment, rowToUpdate);
    else if (ui->lineEdit_type->text() == HOUSE)
        updateExtended(fields_house, rowToUpdate);
    else if (ui->lineEdit_type->text() == OFFICE)
        updateExtended(fields_office, rowToUpdate);
    else
        return;

    if (model->submitAll() && extendedModel->submitAll()) {
        QMessageBox::information(this, "Успех", "Изменения сохранены");
        emit saveButtonClicked();
    } else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так...");
    }
}

void objectOverview::updateExtended(const std::vector<QString> vector, int rowToUpdate) {
    int size = vector.size();
    QModelIndex tempIndex;
    QVariant tempData;

    for (int i = 0; i < size; i++) {
        tempIndex = itemModel->index(i, 1);
        tempData = itemModel->data(tempIndex);

        tempIndex = extendedModel->index(rowToUpdate, i + 1);
        extendedModel->setData(tempIndex, tempData);
    }
}
