#include "objectadding.h"
#include "ui_objectadding.h"

objectAdding::objectAdding(QWidget *parent, QSqlTableModel* model) :
    QWidget(parent),
    ui(new Ui::objectAdding)
{
    ui->setupUi(this);

    this->parent = parent;
    this->model = model;
    extendedModel = new QSqlTableModel();

    ui->comboBox_deal->setCurrentIndex(-1);
    ui->comboBox_district->setCurrentIndex(-1);
    ui->comboBox_type->setCurrentIndex(-1);

    ui->lineEdit_ID->setReadOnly(true);

    QDoubleValidator* doubleValidator = new QDoubleValidator();
    QIntValidator* intValidator = new QIntValidator();

    ui->lineEdit_floor_amount->setValidator(intValidator);
    ui->lineEdit_year->setValidator(intValidator);
    ui->lineEdit_price->setValidator(doubleValidator);
    ui->lineEdit_square->setValidator(doubleValidator);

    QSqlTableModel* tempModel = new QSqlTableModel();
    QModelIndex index;
    QVariant data;

    tempModel->setTable(DISTRICTS);
    tempModel->select();

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 0);
        data = tempModel->data(index);

        ui->comboBox_district->addItem(data.toString());
    }

    QString dealsArr[] = DEALS_ARR;
    int dealsSize = sizeof(dealsArr) / sizeof(dealsArr[0]);
    for (int i = 0; i < dealsSize; i++) {
        ui->comboBox_deal->addItem(dealsArr[i]);

    }

    QString propertyArr[] = PROPERTY_ARR;
    int propertySize = sizeof(propertyArr) / sizeof(propertyArr[0]);
    for (int i = 0; i < propertySize; i++) {
        ui->comboBox_type->addItem(propertyArr[i]);
    }

    int newID = generateID();
    ui->lineEdit_ID->setText(QString::number(newID));

    itemModel = new QStandardItemModel(0, 2);

}

objectAdding::~objectAdding()
{
    delete ui;

    delete extendedModel;
    delete itemModel;


    if (apartment != nullptr)
        delete apartment;
    if (house != nullptr)
        delete house;
    if (office != nullptr)
        delete office;
}

int objectAdding::generateID() {
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

bool objectAdding::checkEmpty() {
    bool res = true;

    if (ui->comboBox_type->currentIndex() == -1) {
        ui->comboBox_type->setStyleSheet("border: 1px solid red;");
        res = false;
    }


    if (ui->comboBox_deal->currentIndex() == -1) {
        ui->comboBox_deal->setStyleSheet("border: 1px solid red;");
        res = false;
    }

    if (ui->comboBox_district->currentIndex() == -1) {
        ui->comboBox_district->setStyleSheet("border: 1px solid red;");
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

void objectAdding::fillTableHeaders(QStandardItemModel* model) {
    QString fields[9];
    int sizeOfVect = 0;

    if (ui->comboBox_type->currentText() == APARTMENT_RUS) {
        sizeOfVect = fields_apartment.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_apartment[i];
        }
    }
    else if (ui->comboBox_type->currentText() == HOUSE_RUS) {
        sizeOfVect = fields_house.size();

        for (int i = 0; i < sizeOfVect; i++) {
            fields[i] = fields_house[i];
        }
    }
    else if (ui->comboBox_type->currentText() == OFFICE_RUS) {
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

bool objectAdding::fillInherited(QString properyType) {
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

QVariant objectAdding::getDataFromItemModel(int row) {
    QModelIndex tempIndex;
    QVariant tempData;

    tempIndex = itemModel->index(row, 1);
    tempData = itemModel->data(tempIndex);

    return tempData;
}

bool objectAdding::setСommonFields(RealEstate* estate) {
    try {
        estate->setID(ui->lineEdit_ID->text().toInt());
        estate->setPropertyType(ui->comboBox_type->currentText());
        estate->setDealType(ui->comboBox_deal->currentText());
        estate->setDescription(ui->plainTextEdit_description->toPlainText());
        estate->setDistrict(ui->comboBox_district->currentText());
        estate->setAddress(ui->lineEdit_address->text());
        estate->setSquare(ui->lineEdit_square->text().toDouble());
        estate->setConstructionYear(ui->lineEdit_year->text().toInt());
        estate->setFloorsAmount(ui->lineEdit_floor_amount->text().toInt());
        estate->setPrice(ui->lineEdit_price->text().toDouble());
    }
    catch (QString errorMessage) {
        QMessageBox::warning(this, "Предупреждение", errorMessage);
        return false;
    }

    int rowToUpdate = model->rowCount();
    model->insertRow(rowToUpdate);
    QModelIndex index;

    index = model->index(rowToUpdate, ID_COL);
    model->setData(index, estate->getID());

    index = model->index(rowToUpdate, DEAL_TYPE_COL);
    model->setData(index, estate->getDealType());

    index = model->index(rowToUpdate, DESCRIPTION_COL);
    model->setData(index, estate->getDescription());

    index = model->index(rowToUpdate, DISTRICT_COL);
    model->setData(index, estate->getDistrict());

    index = model->index(rowToUpdate, ADDRESS_COL);
    model->setData(index, estate->getAddress());

    index = model->index(rowToUpdate, SQUARE_COL);
    model->setData(index, estate->getSquare());

    index = model->index(rowToUpdate, YEAR_COL);
    model->setData(index, estate->getConstructionYear());

    index = model->index(rowToUpdate, FLOOR_AMOUNT_COL);
    model->setData(index, estate->getFloorsAmount());

    index = model->index(rowToUpdate, PRICE_COL);
    model->setData(index, estate->getPrice());

    index = model->index(rowToUpdate, PROPERTY_TYPE_COL);
    model->setData(index, estate->getPropertyType());

    return true;
}

void objectAdding::on_pushButton_save_clicked()
{
    if (!checkEmpty()) {
        QMessageBox::warning(this, "Предупреждение", "Подсвеченное красным не может быть пустым!");
        return;
    }

    QString propertyType = ui->comboBox_type->currentText();

    if (propertyType == APARTMENT_RUS) {
        apartment = new Apartment();
        if(!setСommonFields(apartment))
            return;
    }
    else if (propertyType == HOUSE_RUS) {
        house = new House();
        if (!setСommonFields(house))
            return;
    }
    else if (propertyType == OFFICE_RUS) {
        office = new Office();
        if (!setСommonFields(office))
            return;
    }
    else
        return;

    if (!fillInherited(propertyType)) {
        return;
    }

    QModelIndex index;
    int rowToAdd;

    if (propertyType == APARTMENT_RUS) {
        extendedModel->setTable(APARTMENT_ENG);
        extendedModel->select();
        rowToAdd = extendedModel->rowCount();
        extendedModel->insertRow(rowToAdd);

        index = extendedModel->index(rowToAdd, ID_COL);
        extendedModel->setData(index, apartment->getID());

        index = extendedModel->index(rowToAdd, APARTMENT_KITCHEN_COL);
        extendedModel->setData(index, (apartment->getSquareKitchen() == -1.0) ? QVariant() : apartment->getSquareKitchen());

        index = extendedModel->index(rowToAdd, APARTMENT_ALL_FLOORS_COL);
        extendedModel->setData(index, (apartment->getAllFloorsAmount() == -1) ? QVariant() : apartment->getAllFloorsAmount());

        index = extendedModel->index(rowToAdd, APARTMENT_LAYOUT_COL);
        extendedModel->setData(index, apartment->getLayoutType().isEmpty() ? QVariant() : apartment->getLayoutType());

        index = extendedModel->index(rowToAdd, APARTMENT_BALCONY_COL);
        extendedModel->setData(index, apartment->getHasBalcony().isEmpty() ? QVariant() : apartment->getHasBalcony());

        index = extendedModel->index(rowToAdd, APARTMENT_ELEVATOR_COL);
        extendedModel->setData(index, apartment->getHasElevator().isEmpty() ? QVariant() : apartment->getHasElevator());

        index = extendedModel->index(rowToAdd, APARTMENT_CEILING_COL);
        extendedModel->setData(index, (apartment->getCeilingHeight() == -1.0) ? QVariant() : apartment->getCeilingHeight());

        index = extendedModel->index(rowToAdd, APARTMENT_PARKING_COL);
        extendedModel->setData(index, apartment->getHasParking().isEmpty() ? QVariant() : apartment->getHasParking());

        index = extendedModel->index(rowToAdd, APARTMENT_CONCIERGE_COL);
        extendedModel->setData(index, apartment->getHasConcierge().isEmpty() ? QVariant() : apartment->getHasConcierge());
    }
    else if (propertyType == HOUSE_RUS) {
        extendedModel->setTable(HOUSE_ENG);
        extendedModel->select();
        rowToAdd = extendedModel->rowCount();
        extendedModel->insertRow(rowToAdd);

        index = extendedModel->index(rowToAdd, ID_COL);
        extendedModel->setData(index, house->getID());

        index = extendedModel->index(rowToAdd, HOUSE_LAND_COL);
        extendedModel->setData(index, (house->getLandSquare() == -1.0) ? QVariant() : house->getLandSquare());

        index = extendedModel->index(rowToAdd, HOUSE_KITCHEN_COL);
        extendedModel->setData(index, (house->getKitchenSquare() == -1.0) ? QVariant() : house->getKitchenSquare());

        index = extendedModel->index(rowToAdd, HOUSE_WALL_COL);
        extendedModel->setData(index, house->getWallMaterial().isEmpty() ? QVariant() : house->getWallMaterial());

        index = extendedModel->index(rowToAdd, HOUSE_ROOF_COL);
        extendedModel->setData(index, house->getRoofMaterial().isEmpty() ? QVariant() : house->getRoofMaterial());

        index = extendedModel->index(rowToAdd, HOUSE_FIREPLACE_COL);
        extendedModel->setData(index, house->getHasFireplace().isEmpty() ? QVariant() : house->getHasFireplace());

        index = extendedModel->index(rowToAdd, HOUSE_GARAGE_COL);
        extendedModel->setData(index, house->getHasGarage().isEmpty() ? QVariant() : house->getHasGarage());

        index = extendedModel->index(rowToAdd, HOUSE_HEATING_COL);
        extendedModel->setData(index, house->getHeatingType().isEmpty() ? QVariant() : house->getHeatingType());

        index = extendedModel->index(rowToAdd, HOUSE_SANITATION_COL);
        extendedModel->setData(index, house->getSanitation().isEmpty() ? QVariant() : house->getSanitation());

        index = extendedModel->index(rowToAdd, HOUSE_WATER_COL);
        extendedModel->setData(index, house->getWaterSupply().isEmpty() ? QVariant() : house->getWaterSupply());
    }
    else if (propertyType == OFFICE_RUS) {
        extendedModel->setTable(OFFICE_ENG);
        extendedModel->select();
        rowToAdd = extendedModel->rowCount();
        extendedModel->insertRow(rowToAdd);

        index = extendedModel->index(rowToAdd, ID_COL);
        extendedModel->setData(index, office->getID());

        index = extendedModel->index(rowToAdd, OFFICE_CLASS);
        extendedModel->setData(index, office->getOfficeClass().isEmpty() ? QVariant() : office->getOfficeClass());

        index = extendedModel->index(rowToAdd, OFFICE_ALL_FLOORS_COL);
        extendedModel->setData(index, (office->getAllFloorsAmount() == -1) ? QVariant() : office->getAllFloorsAmount());

        index = extendedModel->index(rowToAdd, OFFICE_WORKSTATIONS_COL);
        extendedModel->setData(index, (office->getWorkstationsAmount() == -1) ? QVariant() : office->getWorkstationsAmount());

        index = extendedModel->index(rowToAdd, OFFICE_WALL_COL);
        extendedModel->setData(index, office->getWallMaterial().isEmpty() ? QVariant() : office->getWallMaterial());

        index = extendedModel->index(rowToAdd, OFFICE_RENOVATION_COL);
        extendedModel->setData(index, office->getRenovation().isEmpty() ? QVariant() : office->getRenovation());

        index = extendedModel->index(rowToAdd, OFFICE_CONFERENCE_COL);
        extendedModel->setData(index, office->getHasConferenceRooms().isEmpty() ? QVariant() : office->getHasConferenceRooms());

        index = extendedModel->index(rowToAdd, OFFICE_SECURITY_COL);
        extendedModel->setData(index, office->getHasSecurityFeatures().isEmpty() ? QVariant() : office->getHasSecurityFeatures());

        index = extendedModel->index(rowToAdd, OFFICE_TOILET_COL);
        extendedModel->setData(index, office->getHasToilet().isEmpty() ? QVariant() : office->getHasToilet());
    }

    if (model->submitAll() && extendedModel->submitAll()) {
        QMessageBox::information(this, "Успех", "Объект успешно добавлен!");
        parent->close();

    } else {
        QMessageBox::warning(this, "Ошибка", "Что-то пошло не так...");
    }
}

void objectAdding::on_plainTextEdit_description_textChanged()
{
    ui->plainTextEdit_description->setStyleSheet("");
}

void objectAdding::on_lineEdit_address_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_address->setStyleSheet("");
}

void objectAdding::on_lineEdit_square_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_square->setStyleSheet("");
}


void objectAdding::on_lineEdit_year_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_year->setStyleSheet("");
}

void objectAdding::on_lineEdit_floor_amount_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_floor_amount->setStyleSheet("");
}

void objectAdding::on_lineEdit_price_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->lineEdit_price->setStyleSheet("");
}

void objectAdding::on_comboBox_deal_activated(int index)
{
    Q_UNUSED(index);
    ui->comboBox_deal->setStyleSheet("");
}

void objectAdding::on_comboBox_district_activated(int index)
{
    Q_UNUSED(index);
    ui->comboBox_district->setStyleSheet("");
}

void objectAdding::on_comboBox_type_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QStandardItem *valueItem;

    itemModel = new QStandardItemModel(0, 2);
    ui->comboBox_type->setStyleSheet("");
    fillTableHeaders(itemModel);
    itemModel->setHeaderData(0, Qt::Horizontal, "Характеристика");
    itemModel->setHeaderData(1, Qt::Horizontal, "Значение");
    for (int i = 0; i < itemModel->rowCount(); i++) {
        valueItem = new QStandardItem();
        valueItem->setData(QVariant(), Qt::EditRole);

        itemModel->setItem(i, 1, valueItem);
    }

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(itemModel);
}
