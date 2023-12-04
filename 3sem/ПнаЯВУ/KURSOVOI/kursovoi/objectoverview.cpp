#include "objectoverview.h"
#include "ui_objectoverview.h"

objectOverview::objectOverview(QWidget *parent, QSqlTableModel* model, QAbstractItemModel* resModel, QString tableName, int objectRow) :
    QWidget(parent),
    ui(new Ui::objectOverview)
{
    ui->setupUi(this);

    this->parent = parent;
    this->model = model;

    QModelIndex index;
    QVariant data;

    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(DISTRICTS);
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

    tempModel->setTable(ACCOUNTS);
    tempModel->select();

    //установка combobox для сделок
    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 6);
        data = tempModel->data(index);

        if (data.toString() == "rieltor") {
            index = tempModel->index(row, 1);
            ui->comboBox_rieltor->addItem(tempModel->data(index).toString());
        }
    }

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 6);
        data = tempModel->data(index);

        if (data.toString() == "client") {
            index = tempModel->index(row, 1);
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
    ui->lineEdit_ID->setReadOnly(true);
    ui->lineEdit_type->setReadOnly(true);

    ui->pushButton_deal->setEnabled(false);
    ui->comboBox_rieltor->setEnabled(false);
    ui->comboBox_client->setEnabled(false);

    ui->checkBox_auth->setEnabled(false);


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

    delete parent;
    delete model;
    delete extendedModel;
    delete itemModel;
}


void objectOverview::on_checkBox_deal_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->pushButton_deal->setEnabled(true);
        ui->comboBox_rieltor->setEnabled(true);
        ui->checkBox_auth->setEnabled(true);
        //ui->comboBox_client->setEnabled(true);
    }
    else {
        ui->checkBox_auth->setChecked(false);
        ui->checkBox_auth->setEnabled(false);


        ui->pushButton_deal->setEnabled(false);
        ui->comboBox_rieltor->setEnabled(false);
        ui->comboBox_client->setEnabled(false);

        ui->comboBox_rieltor->setCurrentIndex(-1);
        ui->comboBox_client->setCurrentIndex(-1);    }
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
    if (tableName == APARTMENT_ENG) {
        sizeOfVect = fields_apartment.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_apartment[i];
        }
    }
    else if (tableName == HOUSE_ENG) {
        sizeOfVect = fields_house.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_house[i];
        }
    }
    else if (tableName == OFFICE_ENG) {
        sizeOfVect = fields_office.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_office[i];
        }
    }
    else
        return;

    QStandardItem* valueItem;

    for (int i = 0; i < sizeOfVect; i++) {
        valueItem = new QStandardItem(fields[i]);
        model->setItem(i, 0, valueItem);

        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);
    }
}

void objectOverview::on_pushButton_save_clicked()
{
    if (!checkEmptySave()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    QModelIndex index;
    int rowToUpdate = findID(model);

    realEstate = new RealEstate();

    try {
        realEstate->setID(ui->lineEdit_ID->text().toInt());
        realEstate->setPropertyType(ui->lineEdit_type->text());
        realEstate->setDealType(ui->comboBox_deal->currentText());
        realEstate->setDescription(ui->plainTextEdit_description->toPlainText());
        realEstate->setDistrict(ui->comboBox_district->currentText());
        realEstate->setAddress(ui->lineEdit_address->text());
        realEstate->setSquare(ui->lineEdit_square->text().toDouble());
        realEstate->setConstructionYear(ui->lineEdit_year->text().toInt());
        realEstate->setFloorsAmount(ui->lineEdit_floor_amount->text().toInt());
        realEstate->setPrice(ui->lineEdit_price->text().toDouble());
    }
    catch (QString errorMessage) {
        QMessageBox::warning(this, "Предупреждение", errorMessage);
        return;
    }

    QString propertyType = realEstate->getPropertyType();

    if (propertyType == APARTMENT_RUS) {
        apartment = new Apartment(*realEstate);
    }
    else if (propertyType == HOUSE_RUS) {
        house = new House(*realEstate);
    }
    else if (propertyType == OFFICE_RUS) {
        office = new Office(*realEstate);
    }

    if (!fillInherited(propertyType)) {
        return;
    }

    index = model->index(rowToUpdate, DESCRIPTION_COL);
    model->setData(index, realEstate->getDescription());

    index = model->index(rowToUpdate, DISTRICT_COL);
    model->setData(index, realEstate->getDistrict());

    index = model->index(rowToUpdate, ADDRESS_COL);
    model->setData(index, realEstate->getAddress());

    index = model->index(rowToUpdate, PRICE_COL);
    model->setData(index, realEstate->getPrice());

    index = model->index(rowToUpdate, SQUARE_COL);
    model->setData(index, realEstate->getSquare());

    index = model->index(rowToUpdate, YEAR_COL);
    model->setData(index, realEstate->getConstructionYear());

    index = model->index(rowToUpdate, FLOOR_AMOUNT_COL);
    model->setData(index, realEstate->getFloorsAmount());

    index = model->index(rowToUpdate, DEAL_TYPE_COL);
    model->setData(index, realEstate->getDealType());

    rowToUpdate = findID(extendedModel);

    if (propertyType == APARTMENT_RUS) {
        extendedModel->setTable(APARTMENT_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, apartment->getID());

        index = extendedModel->index(rowToUpdate, 1);
        extendedModel->setData(index, (apartment->getSquareKitchen() == -1.0) ? QVariant() : apartment->getSquareKitchen());

        index = extendedModel->index(rowToUpdate, 2);
        extendedModel->setData(index, (apartment->getAllFloorsAmount() == -1) ? QVariant() : apartment->getAllFloorsAmount());

        index = extendedModel->index(rowToUpdate, 3);
        extendedModel->setData(index, apartment->getLayoutType().isEmpty() ? QVariant() : apartment->getLayoutType());

        index = extendedModel->index(rowToUpdate, 4);
        extendedModel->setData(index, apartment->getHasBalcony().isEmpty() ? QVariant() : apartment->getHasBalcony());

        index = extendedModel->index(rowToUpdate, 5);
        extendedModel->setData(index, apartment->getHasElevator().isEmpty() ? QVariant() : apartment->getHasElevator());

        index = extendedModel->index(rowToUpdate, 6);
        extendedModel->setData(index, (apartment->getCeilingHeight() == -1.0) ? QVariant() : apartment->getCeilingHeight());

        index = extendedModel->index(rowToUpdate, 7);
        extendedModel->setData(index, apartment->getHasParking().isEmpty() ? QVariant() : apartment->getHasParking());

        index = extendedModel->index(rowToUpdate, 8);
        extendedModel->setData(index, apartment->getHasConcierge().isEmpty() ? QVariant() : apartment->getHasConcierge());
    }
    else if (propertyType == HOUSE_RUS) {
        extendedModel->setTable(HOUSE_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, house->getID());

        index = extendedModel->index(rowToUpdate, 1);
        extendedModel->setData(index, (house->getLandSquare() == -1.0) ? QVariant() : house->getLandSquare());

        index = extendedModel->index(rowToUpdate, 2);
        extendedModel->setData(index, (house->getKitchenSquare() == -1.0) ? QVariant() : house->getKitchenSquare());

        index = extendedModel->index(rowToUpdate, 3);
        extendedModel->setData(index, house->getWallMaterial().isEmpty() ? QVariant() : house->getWallMaterial());

        index = extendedModel->index(rowToUpdate, 4);
        extendedModel->setData(index, house->getRoofMaterial().isEmpty() ? QVariant() : house->getRoofMaterial());

        index = extendedModel->index(rowToUpdate, 5);
        extendedModel->setData(index, house->getHasFireplace().isEmpty() ? QVariant() : house->getHasFireplace());

        index = extendedModel->index(rowToUpdate, 6);
        extendedModel->setData(index, house->getHasGarage().isEmpty() ? QVariant() : house->getHasGarage());

        index = extendedModel->index(rowToUpdate, 7);
        extendedModel->setData(index, house->getHeatingType().isEmpty() ? QVariant() : house->getHeatingType());

        index = extendedModel->index(rowToUpdate, 8);
        extendedModel->setData(index, house->getSanitation().isEmpty() ? QVariant() : house->getSanitation());

        index = extendedModel->index(rowToUpdate, 9);
        extendedModel->setData(index, house->getWaterSupply().isEmpty() ? QVariant() : house->getWaterSupply());
    }
    else if (propertyType == OFFICE_RUS) {
        extendedModel->setTable(OFFICE_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, office->getID());

        index = extendedModel->index(rowToUpdate, 1);
        extendedModel->setData(index, office->getOfficeClass().isEmpty() ? QVariant() : office->getOfficeClass());

        index = extendedModel->index(rowToUpdate, 2);
        extendedModel->setData(index, (office->getAllFloorsAmount() == -1) ? QVariant() : office->getAllFloorsAmount());

        index = extendedModel->index(rowToUpdate, 3);
        extendedModel->setData(index, (office->getWorkstationsAmount() == -1) ? QVariant() : office->getWorkstationsAmount());

        index = extendedModel->index(rowToUpdate, 4);
        extendedModel->setData(index, office->getWallMaterial().isEmpty() ? QVariant() : office->getWallMaterial());

        index = extendedModel->index(rowToUpdate, 5);
        extendedModel->setData(index, office->getRenovation().isEmpty() ? QVariant() : office->getRenovation());

        index = extendedModel->index(rowToUpdate, 6);
        extendedModel->setData(index, office->getHasConferenceRooms().isEmpty() ? QVariant() : office->getHasConferenceRooms());

        index = extendedModel->index(rowToUpdate, 7);
        extendedModel->setData(index, office->getHasSecurityFeatures().isEmpty() ? QVariant() : office->getHasSecurityFeatures());

        index = extendedModel->index(rowToUpdate, 8);
        extendedModel->setData(index, office->getHasToilet().isEmpty() ? QVariant() : office->getHasToilet());
    }

    if (model->submitAll() && extendedModel->submitAll()) {
        QMessageBox::information(this, "Успех", "Изменения сохранены.");
        parent->close();
    }
    else {
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

bool objectOverview::fillInherited(QString properyType) {
    QVariant validCheck;
    if (properyType == APARTMENT_RUS) {
        try {
            validCheck = getDataFromItemModel(0);
            if (!(validCheck.toString() == ""))
                apartment->setSquareKitchen(validCheck.toDouble());

            validCheck = getDataFromItemModel(1);
            if (!(validCheck.toString() == ""))
                apartment->setAllFloorsAmount(validCheck.toInt());

            apartment->setLayoutType(getDataFromItemModel(2).toString());
            apartment->setHasBalcony(getDataFromItemModel(3).toString());
            apartment->setHasElevator(getDataFromItemModel(4).toString());

            validCheck = getDataFromItemModel(5);
            if (!(validCheck.toString() == ""))
                apartment->setCeilingHeight(validCheck.toDouble());

            apartment->setHasParking(getDataFromItemModel(6).toString());
            apartment->setHasConcierge(getDataFromItemModel(7).toString());
        }
        catch (QString errorMessage) {
            QMessageBox::warning(this, "Предупреждение", errorMessage);
            return false;
        }
    }
    else if (properyType == HOUSE_RUS) {
        try {
            validCheck = getDataFromItemModel(0);
            if (!(validCheck.toString() == ""))
                house->setLandSquare(validCheck.toDouble());

            validCheck = getDataFromItemModel(1);
            if (!(validCheck.toString() == ""))
                house->setKitchenSquare(validCheck.toDouble());

            house->setWallMaterial(getDataFromItemModel(2).toString());
            house->setRoofMaterial(getDataFromItemModel(3).toString());
            house->setHasFireplace(getDataFromItemModel(4).toString());
            house->setHasGarage(getDataFromItemModel(5).toString());
            house->setHeatingType(getDataFromItemModel(6).toString());
            house->setSanitation(getDataFromItemModel(7).toString());
            house->setWaterSupply(getDataFromItemModel(8).toString());
        }
        catch (QString errorMessage) {
            QMessageBox::warning(this, "Предупреждение", errorMessage);
            return false;
        }
    }
    else if (properyType == OFFICE_RUS) {
        try {
            office->setOfficeClass(getDataFromItemModel(0).toString());

            validCheck = getDataFromItemModel(1);
            if (!(validCheck.toString() == ""))
                office->setAllFloorsAmount(validCheck.toInt());

            validCheck = getDataFromItemModel(2);
            if (!(validCheck.toString() == ""))
                office->setWorkstationsAmount(validCheck.toInt());

            office->setWallMaterial(getDataFromItemModel(3).toString());
            office->setRenovation(getDataFromItemModel(4).toString());
            office->setHasConferenceRooms(getDataFromItemModel(5).toString());
            office->setHasSecurityFeatures(getDataFromItemModel(6).toString());
            office->setHasToilet(getDataFromItemModel(7).toString());
        }
        catch (QString errorMessage) {
            QMessageBox::warning(this, "Предупреждение", errorMessage);
            return false;
        }
    }
    return true;
}

bool objectOverview::checkEmptySave() {
    bool res = true;

    if (ui->comboBox_deal->currentIndex() == -1) {
        ui->comboBox_deal->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->plainTextEdit_description->toPlainText().isEmpty()) {
        ui->plainTextEdit_description->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_address->text().isEmpty()) {
        ui->lineEdit_address->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_square->text().isEmpty()) {
        ui->lineEdit_square->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_floor_amount->text().isEmpty()) {
        ui->lineEdit_floor_amount->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_year->text().isEmpty()) {
        ui->lineEdit_year->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->lineEdit_price->text().isEmpty()) {
        ui->lineEdit_price->setStyleSheet("border: 1px solid red;");
        res = false;
    }
    return res;
}

bool objectOverview::checkEmptyDeal() {
    bool res = true;

    if (ui->comboBox_rieltor->currentIndex() == -1) {
        ui->comboBox_rieltor->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    return res;
}

bool objectOverview::checkEmptyAuth() {
    bool res = true;

    if (ui->comboBox_client->currentIndex() == -1) {
        ui->comboBox_client->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    return res;
}

void objectOverview::on_plainTextEdit_description_textChanged()
{
    ui->plainTextEdit_description->setStyleSheet("");
}


void objectOverview::on_lineEdit_address_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_address->setStyleSheet("");
}


void objectOverview::on_lineEdit_price_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_price->setStyleSheet("");
}


void objectOverview::on_lineEdit_square_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_square->setStyleSheet("");
}


void objectOverview::on_lineEdit_year_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_year->setStyleSheet("");
}

void objectOverview::on_lineEdit_floor_amount_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_floor_amount->setStyleSheet("");
}

void objectOverview::on_pushButton_deal_clicked()
{
    if (!checkEmptyDeal()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    if (ui->checkBox_auth->isChecked() && !checkEmptyAuth()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    QDialog* dialog = new QDialog();

    if (ui->checkBox_auth->isChecked())
        makeDeal = new MakeDeal(dialog, ui->lineEdit_ID->text(), ui->comboBox_rieltor->currentText(), ui->comboBox_client->currentText());
    else
        makeDeal = new MakeDeal(dialog, ui->lineEdit_ID->text(), ui->comboBox_rieltor->currentText());

    dialog->setModal(true);
    dialog->setWindowTitle("Заключение сделки");
    dialog->setFixedSize(300, 200);
    makeDeal->setParent(dialog);
    makeDeal->show();

    dialog->exec();
}

void objectOverview::on_comboBox_rieltor_activated(int index)
{
    Q_UNUSED(index);
    ui->comboBox_rieltor->setStyleSheet("");
}


void objectOverview::on_comboBox_client_activated(int index)
{
    Q_UNUSED(index);
    ui->comboBox_client->setStyleSheet("");
}

void objectOverview::on_checkBox_auth_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_client->setEnabled(true);
    }
    else {
        ui->comboBox_client->setCurrentIndex(-1);
        ui->comboBox_client->setEnabled(false);
        ui->comboBox_client->setStyleSheet("");
    }
}

QVariant objectOverview::getDataFromItemModel(int row) {
    QModelIndex tempIndex;
    QVariant tempData;

    tempIndex = itemModel->index(row, 1);
    tempData = itemModel->data(tempIndex);

    return tempData;
}

