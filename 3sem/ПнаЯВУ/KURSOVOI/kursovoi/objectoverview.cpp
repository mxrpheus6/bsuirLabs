#include "objectoverview.h"
#include "ui_objectoverview.h"

objectOverview::objectOverview(QWidget *parent, QSqlTableModel* model, QAbstractItemModel* resModel, QString tableName, int objectRow, QString access, int ID) :
    QWidget(parent),
    ui(new Ui::objectOverview)
{
    ui->setupUi(this);

    this->parent = parent;
    this->model = model;
    userID = ID;

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
        index = tempModel->index(row, ACCESS_COL);
        data = tempModel->data(index);

        if (data.toString() == "rieltor") {
            index = tempModel->index(row, NAME_COL);
            ui->comboBox_rieltor->addItem(tempModel->data(index).toString());
        }
    }

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, ACCESS_COL);
        data = tempModel->data(index);

        if (data.toString() == "client") {
            index = tempModel->index(row, NAME_COL);
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

    doubleValidator = new QDoubleValidator();
    intValidator = new QIntValidator();

    ui->lineEdit_price->setValidator(doubleValidator);
    ui->lineEdit_square->setValidator(doubleValidator);
    ui->lineEdit_year->setValidator(intValidator);
    ui->lineEdit_floor_amount->setValidator(intValidator);

    if (access == "rieltor") {
        ui->pushButton_request->setEnabled(false);
        ui->pushButton_request->setVisible(false);

        isRequested = setRequests();
        setPurhcases();
    }
    else if (access == "client") {
        ui->pushButton_deal->setEnabled(false);
        ui->pushButton_deal->setVisible(false);
        ui->pushButton_request->setGeometry(230, 290, 251, 51);


        ui->plainTextEdit_description->setReadOnly(true);
        ui->lineEdit_address->setReadOnly(true);
        ui->lineEdit_floor_amount->setReadOnly(true);
        ui->lineEdit_price->setReadOnly(true);
        ui->lineEdit_square->setReadOnly(true);
        ui->lineEdit_year->setReadOnly(true);

        ui->comboBox_district->setEnabled(false);
        ui->comboBox_deal->setEnabled(false);
        ui->comboBox_rieltor->setEnabled(false);
        ui->comboBox_rieltor->setVisible(false);
        ui->comboBox_client->setEnabled(false);
        ui->comboBox_client->setVisible(false);

        ui->checkBox_auth->setVisible(false);
        ui->checkBox_deal->setVisible(false);

        ui->tableView_extended->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->pushButton_save->setEnabled(false);
        ui->pushButton_save->setVisible(false);
        ui->pushButton_deal->setEnabled(false);
        ui->pushButton_deal->setVisible(false);

        ui->label_client->setVisible(false);
        ui->label_rieltor->setVisible(false);
    }


    extendedModel = new QSqlTableModel(this);
    extendedModel->setTable(tableName);
    extendedModel->select();

    itemModel = new QStandardItemModel(0, 2);

    fillTableHeaders(itemModel, tableName);

    int rowOfObject = findID(extendedModel, ui->lineEdit_ID->text().toInt());

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

    delete tempModel;
}



objectOverview::~objectOverview()
{
    delete ui;

    delete extendedModel;
    delete itemModel;

    delete doubleValidator;
    delete intValidator;

    if (realEstate != nullptr)
        delete realEstate;
    if (apartment != nullptr)
        delete apartment;
    if (house != nullptr)
        delete house;
    if (office != nullptr)
        delete office;
    if (makeDeal != nullptr)
        delete makeDeal;
}

bool objectOverview::setRequests() {
    QSqlTableModel* tempModelReq = new QSqlTableModel();
    tempModelReq->setTable(REQUESTS);
    tempModelReq->select();

    QSqlTableModel* tempModelAcc = new QSqlTableModel();
    tempModelAcc->setTable(ACCOUNTS);
    tempModelAcc->select();

    QModelIndex index;
    QString name;
    int clientRow = -1;

    for (int row = 0; row < tempModelReq->rowCount(); row++) {
        index = tempModelReq->index(row, ID_COL);
        if (tempModelReq->data(index).toInt() == ui->lineEdit_ID->text().toInt()) {
            index = tempModelReq->index(row, ID_CLIENT_REQ);    //id клиента
            clientRow = findID(tempModelAcc, tempModelReq->data(index).toInt());
            break;
        }
    }

    if (clientRow == -1) {
        return false;
    }

    index = tempModelAcc->index(clientRow, NAME_COL);      //имя клиента
    name = tempModelAcc->data(index).toString();

    delete tempModelAcc;
    delete tempModelReq;

    for (int i = 0; i < ui->comboBox_client->count(); i++) {
        if (ui->comboBox_client->itemText(i) == name) {
            ui->comboBox_client->setCurrentIndex(i);

            ui->checkBox_deal->setEnabled(false);
            ui->checkBox_deal->setChecked(true);
            ui->checkBox_auth->setEnabled(false);
            ui->checkBox_auth->setChecked(true);

            ui->comboBox_client->setEnabled(false);
            return true;
        }
    }
    return false;
}

void objectOverview::setPurhcases() {
    QSqlTableModel* tempModelDeals = new QSqlTableModel();
    tempModelDeals->setTable(DEALS);
    tempModelDeals->select();

    QSqlTableModel* tempModelAcc = new QSqlTableModel();
    tempModelAcc->setTable(ACCOUNTS);
    tempModelAcc->select();

    QModelIndex index;
    QString rieltorName;
    QString clientName;
    int rieltorRow = -1;
    int clientRow = -1;

    for (int row = 0; row < tempModelDeals->rowCount(); row++) {
        index = tempModelDeals->index(row, ID_COL);
        if (tempModelDeals->data(index).toInt() == ui->lineEdit_ID->text().toInt()) {
            index = tempModelDeals->index(row, ID_RIELTOR);    //id риелтора
            rieltorRow = findID(tempModelAcc, tempModelDeals->data(index).toInt());
            index = tempModelDeals->index(row, ID_CLIENT_DEAL);    //id клиента
            clientRow = findID(tempModelAcc, tempModelDeals->data(index).toInt());
            break;
        }
    }

    if (clientRow == -1 || rieltorRow == -1) {
        return;
    }

    index = tempModelAcc->index(rieltorRow, NAME_COL);      //имя риелтора
    rieltorName = tempModelAcc->data(index).toString();

    index = tempModelAcc->index(clientRow, NAME_COL);      //имя клиента
    clientName = tempModelAcc->data(index).toString();

    for (int i = 0; i < ui->comboBox_rieltor->count(); i++) {
        if (ui->comboBox_rieltor->itemText(i) == rieltorName) {
            ui->comboBox_rieltor->setCurrentIndex(i);
        }
    }

    for (int i = 0; i < ui->comboBox_client->count(); i++) {
        if (ui->comboBox_client->itemText(i) == clientName) {
            ui->comboBox_client->setCurrentIndex(i);
        }
    }

    ui->checkBox_deal->setEnabled(false);
    ui->checkBox_deal->setChecked(true);
    ui->checkBox_auth->setEnabled(false);
    ui->checkBox_auth->setChecked(true);

    ui->pushButton_deal->setEnabled(false);

    ui->comboBox_deal->setEnabled(false);
    ui->comboBox_rieltor->setEnabled(false);
    ui->comboBox_client->setEnabled(false);

    delete tempModelAcc;
    delete tempModelDeals;
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

int objectOverview::findID(QAbstractItemModel* model, int ID) {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < model->rowCount(); row++) {
        index = model->index(row, ID_COL);
        data = model->data(index);
        if (data.toInt() == ID)
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

    for (int i = 0; i < sizeOfVect; i++) {
        QStandardItem* valueItem = new QStandardItem(fields[i]);
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
    int rowToUpdate = findID(model, ui->lineEdit_ID->text().toInt());

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

    rowToUpdate = findID(extendedModel, ui->lineEdit_ID->text().toInt());

    if (propertyType == APARTMENT_RUS) {
        extendedModel->setTable(APARTMENT_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, apartment->getID());

        index = extendedModel->index(rowToUpdate, APARTMENT_KITCHEN_COL);
        extendedModel->setData(index, (apartment->getSquareKitchen() == -1.0) ? QVariant() : apartment->getSquareKitchen());

        index = extendedModel->index(rowToUpdate, APARTMENT_ALL_FLOORS_COL);
        extendedModel->setData(index, (apartment->getAllFloorsAmount() == -1) ? QVariant() : apartment->getAllFloorsAmount());

        index = extendedModel->index(rowToUpdate, APARTMENT_LAYOUT_COL);
        extendedModel->setData(index, apartment->getLayoutType().isEmpty() ? QVariant() : apartment->getLayoutType());

        index = extendedModel->index(rowToUpdate, APARTMENT_BALCONY_COL);
        extendedModel->setData(index, apartment->getHasBalcony().isEmpty() ? QVariant() : apartment->getHasBalcony());

        index = extendedModel->index(rowToUpdate, APARTMENT_ELEVATOR_COL);
        extendedModel->setData(index, apartment->getHasElevator().isEmpty() ? QVariant() : apartment->getHasElevator());

        index = extendedModel->index(rowToUpdate, APARTMENT_CEILING_COL);
        extendedModel->setData(index, (apartment->getCeilingHeight() == -1.0) ? QVariant() : apartment->getCeilingHeight());

        index = extendedModel->index(rowToUpdate, APARTMENT_PARKING_COL);
        extendedModel->setData(index, apartment->getHasParking().isEmpty() ? QVariant() : apartment->getHasParking());

        index = extendedModel->index(rowToUpdate, APARTMENT_CONCIERGE_COL);
        extendedModel->setData(index, apartment->getHasConcierge().isEmpty() ? QVariant() : apartment->getHasConcierge());
    }
    else if (propertyType == HOUSE_RUS) {
        extendedModel->setTable(HOUSE_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, house->getID());

        index = extendedModel->index(rowToUpdate, HOUSE_LAND_COL);
        extendedModel->setData(index, (house->getLandSquare() == -1.0) ? QVariant() : house->getLandSquare());

        index = extendedModel->index(rowToUpdate, HOUSE_KITCHEN_COL);
        extendedModel->setData(index, (house->getKitchenSquare() == -1.0) ? QVariant() : house->getKitchenSquare());

        index = extendedModel->index(rowToUpdate, HOUSE_WALL_COL);
        extendedModel->setData(index, house->getWallMaterial().isEmpty() ? QVariant() : house->getWallMaterial());

        index = extendedModel->index(rowToUpdate, HOUSE_ROOF_COL);
        extendedModel->setData(index, house->getRoofMaterial().isEmpty() ? QVariant() : house->getRoofMaterial());

        index = extendedModel->index(rowToUpdate, HOUSE_FIREPLACE_COL);
        extendedModel->setData(index, house->getHasFireplace().isEmpty() ? QVariant() : house->getHasFireplace());

        index = extendedModel->index(rowToUpdate, HOUSE_GARAGE_COL);
        extendedModel->setData(index, house->getHasGarage().isEmpty() ? QVariant() : house->getHasGarage());

        index = extendedModel->index(rowToUpdate, HOUSE_HEATING_COL);
        extendedModel->setData(index, house->getHeatingType().isEmpty() ? QVariant() : house->getHeatingType());

        index = extendedModel->index(rowToUpdate, HOUSE_SANITATION_COL);
        extendedModel->setData(index, house->getSanitation().isEmpty() ? QVariant() : house->getSanitation());

        index = extendedModel->index(rowToUpdate, HOUSE_WATER_COL);
        extendedModel->setData(index, house->getWaterSupply().isEmpty() ? QVariant() : house->getWaterSupply());
    }
    else if (propertyType == OFFICE_RUS) {
        extendedModel->setTable(OFFICE_ENG);
        extendedModel->select();

        index = extendedModel->index(rowToUpdate, ID_COL);
        extendedModel->setData(index, office->getID());

        index = extendedModel->index(rowToUpdate, OFFICE_CLASS);
        extendedModel->setData(index, office->getOfficeClass().isEmpty() ? QVariant() : office->getOfficeClass());

        index = extendedModel->index(rowToUpdate, OFFICE_ALL_FLOORS_COL);
        extendedModel->setData(index, (office->getAllFloorsAmount() == -1) ? QVariant() : office->getAllFloorsAmount());

        index = extendedModel->index(rowToUpdate, OFFICE_WORKSTATIONS_COL);
        extendedModel->setData(index, (office->getWorkstationsAmount() == -1) ? QVariant() : office->getWorkstationsAmount());

        index = extendedModel->index(rowToUpdate, OFFICE_WALL_COL);
        extendedModel->setData(index, office->getWallMaterial().isEmpty() ? QVariant() : office->getWallMaterial());

        index = extendedModel->index(rowToUpdate, OFFICE_RENOVATION_COL);
        extendedModel->setData(index, office->getRenovation().isEmpty() ? QVariant() : office->getRenovation());

        index = extendedModel->index(rowToUpdate, OFFICE_CONFERENCE_COL);
        extendedModel->setData(index, office->getHasConferenceRooms().isEmpty() ? QVariant() : office->getHasConferenceRooms());

        index = extendedModel->index(rowToUpdate, OFFICE_SECURITY_COL);
        extendedModel->setData(index, office->getHasSecurityFeatures().isEmpty() ? QVariant() : office->getHasSecurityFeatures());

        index = extendedModel->index(rowToUpdate, OFFICE_TOILET_COL);
        extendedModel->setData(index, office->getHasToilet().isEmpty() ? QVariant() : office->getHasToilet());
    }

    if (model->submitAll() && extendedModel->submitAll()) {
        QMessageBox::information(this, "Успех", "Изменения сохранены.");
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

    QDialog* dialog = new QDialog(this);

    if (ui->checkBox_auth->isChecked())
        makeDeal = new MakeDeal(dialog, parent, isRequested, ui->lineEdit_ID->text(), ui->comboBox_rieltor->currentText(), ui->comboBox_client->currentText());
    else
        makeDeal = new MakeDeal(dialog, parent, isRequested, ui->lineEdit_ID->text(), ui->comboBox_rieltor->currentText());

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

void objectOverview::on_pushButton_request_clicked()
{
    QSqlTableModel* tempModelReq = new QSqlTableModel();
    tempModelReq->setTable(REQUESTS);
    tempModelReq->select();

    QModelIndex index;

    for (int row = 0; row < tempModelReq->rowCount(); row++) {
        index = tempModelReq->index(row, ID_CLIENT_REQ);
        if (tempModelReq->data(index).toInt() == userID) {
            QMessageBox::information(this, "Информация", "Вы можете оставить только одну заявку. С вами скоро свяжется риелтор!");
            return;
        }
    }

    for (int row = 0; row < tempModelReq->rowCount(); row++) {
        index = tempModelReq->index(row, ID_COL);
        if (tempModelReq->data(index).toInt() == ui->lineEdit_ID->text().toInt()) {
            index = tempModelReq->index(row, ID_CLIENT_REQ);
            if (tempModelReq->data(index).toInt() != userID) {
                QMessageBox::information(this, "Информация", "Кто-то другой уже оставил заявку на этот объект. В случае отклонения этой заявки, вы сможете оставить заявку.");
                return;
            }
        }
    }

    int rowToAdd = tempModelReq->rowCount();
    tempModelReq->insertRow(rowToAdd);

    index = tempModelReq->index(rowToAdd, ID_COL);
    tempModelReq->setData(index, ui->lineEdit_ID->text());

    index = tempModelReq->index(rowToAdd, ID_CLIENT_REQ);
    tempModelReq->setData(index, userID);

    if (tempModelReq->submitAll()) {
        QMessageBox::information(this, "Успех", "Заявка успешно оформлена!");
        parent->close();

    } else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так...");
    }

    delete tempModelReq;
}
