#include "realestatebase.h"
#include "ui_realestatebase.h"

RealEstateBase::RealEstateBase(QWidget *parent, QString mode, QString access, int ID) :
    QWidget(parent),
    ui(new Ui::RealEstateBase)
{
    ui->setupUi(this);

    this->mode = mode;
    this->access = access;
    userID = ID;

    model = new QSqlTableModel(this);
    model->setTable(ESTATE);
    createEmptyTable(model);

    model->select();

    resModel = model;

    setFilters();

    ui->tableView_estate->setModel(resModel);


    QStringList uniqueValues;
    QModelIndex index;
    QVariant value;

    //заполнение combobox
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

    QSqlTableModel* tempModel = new QSqlTableModel();

    tempModel->setTable(DISTRICTS);
    tempModel->select();

    for (int row = 0; row < tempModel->rowCount(); row++) {
        index = tempModel->index(row, 0);
        value = tempModel->data(index);

        ui->comboBox_district->addItem(value.toString());
    }

    delete tempModel;

    for (int row = 0; row < model->rowCount(); ++row) {
        index = model->index(row, FLOOR_AMOUNT_COL);
        value = model->data(index);
        if (!uniqueValues.contains(value.toString())) {
            uniqueValues << value.toString();
        }
    }
    std::sort(uniqueValues.begin(), uniqueValues.end(), RealEstateBase::numericCompare);
    ui->comboBox_floor_amount->addItems(uniqueValues);
    uniqueValues.clear();


    //отключение combobox
    ui->comboBox_type->setEnabled(false);
    ui->comboBox_deal->setEnabled(false);
    ui->comboBox_district->setEnabled(false);
    ui->comboBox_floor_amount->setEnabled(false);

    //помещение в combobox placeholder
    ui->comboBox_type->setCurrentIndex(-1);
    ui->comboBox_deal->setCurrentIndex(-1);
    ui->comboBox_district->setCurrentIndex(-1);
    ui->comboBox_floor_amount->setCurrentIndex(-1);

    doubleValidator = new QDoubleValidator(this);
    intValidator = new QIntValidator(this);

    //установка валидаторов и отключение lineedit
    ui->lineEdit_square_from->setValidator(doubleValidator);
    ui->lineEdit_square_to->setValidator(doubleValidator);
    ui->lineEdit_square_from->setEnabled(false);
    ui->lineEdit_square_to->setEnabled(false);

    ui->lineEdit_year_from->setValidator(intValidator);
    ui->lineEdit_year_to->setValidator(intValidator);
    ui->lineEdit_year_from->setEnabled(false);
    ui->lineEdit_year_to->setEnabled(false);

    ui->lineEdit_price_from->setValidator(doubleValidator);
    ui->lineEdit_price_to->setValidator(doubleValidator);
    ui->lineEdit_price_from->setEnabled(false);
    ui->lineEdit_price_to->setEnabled(false);

    if (mode == "base") {
        ui->pushButton_reject->setEnabled(false);
        ui->pushButton_reject->setVisible(false);

        if (access == "client") {
            ui->pushButton_add->setEnabled(false);
            ui->pushButton_add->setVisible(false);
            ui->pushButton_delete->setEnabled(false);
            ui->pushButton_delete->setVisible(false);

            ui->pushButton_estate->resize(81, 121);
        }
    }
    else if (mode == "deals") {
        ui->pushButton_add->setEnabled(false);
        ui->pushButton_add->setVisible(false);
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_delete->setVisible(false);

        ui->pushButton_reject->setEnabled(true);
    }
    else if (mode == "purchases") {
        ui->pushButton_reject->setEnabled(false);
        ui->pushButton_reject->setVisible(false);

        ui->pushButton_add->setEnabled(false);
    }
}

RealEstateBase::~RealEstateBase()
{
    delete ui;

    delete model;
    delete resModel;
    delete doubleValidator;
    delete intValidator;
}

bool RealEstateBase::numericCompare(const QString &str1, const QString &str2)
{
    return str1.toInt() < str2.toInt();
}

void RealEstateBase::on_checkBox_type_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_type->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(resModel);
        ui->comboBox_type->setEnabled(false);
        ui->comboBox_type->setCurrentIndex(-1);
        setFilters();
    }
}

void RealEstateBase::on_checkBox_deal_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_deal->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(resModel);
        ui->comboBox_deal->setEnabled(false);
        ui->comboBox_deal->setCurrentIndex(-1);
        setFilters();
    }
}



void RealEstateBase::on_checkBox_district_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_district->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(resModel);
        ui->comboBox_district->setEnabled(false);
        ui->comboBox_district->setCurrentIndex(-1);
        setFilters();
    }
}


void RealEstateBase::on_checkBox_floor_amount_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_floor_amount->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(resModel);
        ui->comboBox_floor_amount->setEnabled(false);
        ui->comboBox_floor_amount->setCurrentIndex(-1);
        setFilters();
    }
}

void RealEstateBase::on_checkBox_square_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->lineEdit_square_from->setEnabled(true);
        ui->lineEdit_square_to->setEnabled(true);
    }
    else {
        ui->lineEdit_square_from->clear();
        ui->lineEdit_square_to->clear();

        ui->tableView_estate->setModel(resModel);
        ui->lineEdit_square_from->setEnabled(false);
        ui->lineEdit_square_to->setEnabled(false);
        setFilters();
    }
}

void RealEstateBase::on_checkBox_year_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->lineEdit_year_from->setEnabled(true);
        ui->lineEdit_year_to->setEnabled(true);
    }
    else {
        ui->lineEdit_year_from->clear();
        ui->lineEdit_year_to->clear();

        ui->tableView_estate->setModel(resModel);
        ui->lineEdit_year_from->setEnabled(false);
        ui->lineEdit_year_to->setEnabled(false);
        setFilters();
    }
}

void RealEstateBase::on_checkBox_price_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->lineEdit_price_from->setEnabled(true);
        ui->lineEdit_price_to->setEnabled(true);
    }
    else {
        ui->lineEdit_price_from->clear();
        ui->lineEdit_price_to->clear();

        ui->tableView_estate->setModel(resModel);
        ui->lineEdit_price_from->setEnabled(false);
        ui->lineEdit_price_to->setEnabled(false);
        setFilters();
    }
}


QStandardItemModel* RealEstateBase::applyFilterCombobox(QAbstractItemModel *originalModel, int colIndex, QComboBox *cb)
{
    QStandardItemModel *newModel = new QStandardItemModel();

    int rowCount = originalModel->rowCount();
    int colCount = originalModel->columnCount();

    for (int col = 0; col < colCount; col++) {
        newModel->setHorizontalHeaderItem(col, new QStandardItem(originalModel->headerData(col, Qt::Horizontal).toString()));
    }

    for (int row = 0; row < rowCount; row++) {
        QModelIndex index = originalModel->index(row, colIndex);
        QVariant data = originalModel->data(index);

        if (data.toString() == cb->currentText())
        {
            QList<QStandardItem*> rowItems;

            for (int col = 0; col < colCount; col++) {
                QModelIndex sourceIndex = originalModel->index(row, col);
                QVariant sourceData = originalModel->data(sourceIndex);

                QStandardItem *item = new QStandardItem(sourceData.toString());
                rowItems.append(item);
            }

            newModel->appendRow(rowItems);
        }
    }
    return newModel;
}

QStandardItemModel* RealEstateBase::applyFilterLineEdit(QAbstractItemModel *originalModel, int colIndex, QLineEdit *from, QLineEdit *to)
{
    QStandardItemModel *newModel = new QStandardItemModel();
    if (originalModel)
    {
        int rowCount = originalModel->rowCount();
        int colCount = originalModel->columnCount();

        for (int col = 0; col < colCount; col++) {
            newModel->setHorizontalHeaderItem(col, new QStandardItem(originalModel->headerData(col, Qt::Horizontal).toString()));
        }

        for (int row = 0; row < rowCount; row++)
        {
            QModelIndex index = originalModel->index(row, colIndex);
            QVariant data = originalModel->data(index);

            double fromValue = -1;
            double toValue = DBL_MAX;

            if (!from->text().isEmpty()) {
                fromValue = from->text().toDouble();
            }
            if (!to->text().isEmpty()) {
                toValue = to->text().toDouble();
            }

            if (data.toDouble() >= fromValue && data.toDouble() <= toValue)
            {
                QList<QStandardItem*> rowItems;

                for (int col = 0; col < colCount; col++) {
                    QModelIndex sourceIndex = originalModel->index(row, col);
                    QVariant sourceData = originalModel->data(sourceIndex);

                    QStandardItem *item = new QStandardItem(sourceData.toString());
                    rowItems.append(item);
                }

                newModel->appendRow(rowItems);
            }
        }
    }
    return newModel;
}

void RealEstateBase::setFilters() {
    model->sort(ID_COL, Qt::AscendingOrder);
    resModel = model;

    if (mode == "base") {
        resModel = baseFilter(resModel);
    }
    else if (mode == "deals") {
        resModel = requestsFilter(resModel);
    }
    else if (mode == "purchases") {
        resModel = purchasesFilter(resModel);
    }

    if (ui->comboBox_type->currentIndex() != -1) {
        resModel= applyFilterCombobox(resModel, PROPERTY_TYPE_COL, ui->comboBox_type);
    }
    if (ui->comboBox_deal->currentIndex() != -1) {
        resModel= applyFilterCombobox(resModel, DEAL_TYPE_COL, ui->comboBox_deal);
    }
    if (ui->comboBox_district->currentIndex() != -1) {
        resModel= applyFilterCombobox(resModel, DISTRICT_COL, ui->comboBox_district);
    }
    if (!ui->lineEdit_square_to->text().isEmpty() || !ui->lineEdit_square_from->text().isEmpty()) {
        resModel= applyFilterLineEdit(resModel, SQUARE_COL, ui->lineEdit_square_from, ui->lineEdit_square_to);
    }
    if (!ui->lineEdit_year_to->text().isEmpty() || !ui->lineEdit_year_from->text().isEmpty()) {
        resModel= applyFilterLineEdit(resModel, YEAR_COL, ui->lineEdit_year_from, ui->lineEdit_year_to);
    }
    if (!ui->lineEdit_price_to->text().isEmpty() || !ui->lineEdit_price_from->text().isEmpty()) {
        resModel= applyFilterLineEdit(resModel, PRICE_COL, ui->lineEdit_price_from, ui->lineEdit_price_to);
    }
    if (ui->comboBox_floor_amount->currentIndex() != -1) {
        resModel= applyFilterCombobox(resModel, FLOOR_AMOUNT_COL, ui->comboBox_floor_amount);
    }
    ui->tableView_estate->setModel(resModel);
}

QStandardItemModel* RealEstateBase::baseFilter(QAbstractItemModel *originalModel) {
    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(DEALS);
    tempModel->select();

    QList<int> idList;
    QModelIndex index;
    int rowCount = tempModel->rowCount();

    for (int row = 0; row < rowCount; row++) {
        index = tempModel->index(row, ID_COL);
        idList.append(tempModel->data(index).toInt());
    }

    delete tempModel;

    QStandardItemModel *newModel = new QStandardItemModel();

    rowCount = originalModel->rowCount();
    int colCount = originalModel->columnCount();

    for (int col = 0; col < colCount; col++) {
        newModel->setHorizontalHeaderItem(col, new QStandardItem(originalModel->headerData(col, Qt::Horizontal).toString()));
    }

    for (int row = 0; row < rowCount; row++) {
        QModelIndex index = originalModel->index(row, ID_COL);
        QVariant data = originalModel->data(index);

        if (!idList.contains(data.toInt()))
        {
            QList<QStandardItem*> rowItems;

            for (int col = 0; col < colCount; col++) {
                QModelIndex sourceIndex = originalModel->index(row, col);
                QVariant sourceData = originalModel->data(sourceIndex);

                QStandardItem *item = new QStandardItem(sourceData.toString());
                rowItems.append(item);
            }

            newModel->appendRow(rowItems);
        }
    }
    return newModel;
}

QStandardItemModel* RealEstateBase::requestsFilter(QAbstractItemModel *originalModel) {
    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(REQUESTS);
    tempModel->select();

    QList<int> idList;
    QModelIndex index;
    int rowCount = tempModel->rowCount();

    for (int row = 0; row < rowCount; row++) {
        index = tempModel->index(row, ID_COL);
        idList.append(tempModel->data(index).toInt());
    }

    delete tempModel;

    QStandardItemModel *newModel = new QStandardItemModel();

    rowCount = originalModel->rowCount();
    int colCount = originalModel->columnCount();

    for (int col = 0; col < colCount; col++) {
        newModel->setHorizontalHeaderItem(col, new QStandardItem(originalModel->headerData(col, Qt::Horizontal).toString()));
    }

    for (int row = 0; row < rowCount; row++) {
        QModelIndex index = originalModel->index(row, ID_COL);
        QVariant data = originalModel->data(index);

        if (idList.contains(data.toInt()))
        {
            QList<QStandardItem*> rowItems;

            for (int col = 0; col < colCount; col++) {
                QModelIndex sourceIndex = originalModel->index(row, col);
                QVariant sourceData = originalModel->data(sourceIndex);

                QStandardItem *item = new QStandardItem(sourceData.toString());
                rowItems.append(item);
            }

            newModel->appendRow(rowItems);
        }
    }
    return newModel;
}

QStandardItemModel* RealEstateBase::purchasesFilter(QAbstractItemModel *originalModel) {
    QSqlTableModel* tempModel = new QSqlTableModel();
    tempModel->setTable(DEALS);
    tempModel->select();

    QList<int> idList;
    QModelIndex index;
    int rowCount = tempModel->rowCount();

    for (int row = 0; row < rowCount; row++) {
        index = tempModel->index(row, ID_COL);
        idList.append(tempModel->data(index).toInt());
    }

    delete tempModel;

    QStandardItemModel *newModel = new QStandardItemModel();

    rowCount = originalModel->rowCount();
    int colCount = originalModel->columnCount();

    for (int col = 0; col < colCount; col++) {
        newModel->setHorizontalHeaderItem(col, new QStandardItem(originalModel->headerData(col, Qt::Horizontal).toString()));
    }

    for (int row = 0; row < rowCount; row++) {
        QModelIndex index = originalModel->index(row, ID_COL);
        QVariant data = originalModel->data(index);

        if (idList.contains(data.toInt()))
        {
            QList<QStandardItem*> rowItems;

            for (int col = 0; col < colCount; col++) {
                QModelIndex sourceIndex = originalModel->index(row, col);
                QVariant sourceData = originalModel->data(sourceIndex);

                QStandardItem *item = new QStandardItem(sourceData.toString());
                rowItems.append(item);
            }

            newModel->appendRow(rowItems);
        }
    }
    return newModel;
}

void RealEstateBase::on_lineEdit_square_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_lineEdit_square_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_lineEdit_year_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}


void RealEstateBase::on_lineEdit_year_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_lineEdit_price_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}


void RealEstateBase::on_lineEdit_price_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::createEmptyTable(QSqlTableModel* model) {
    model->setHeaderData(ID_COL, Qt::Horizontal, "ID");
    model->setHeaderData(PROPERTY_TYPE_COL, Qt::Horizontal, "Тип");
    model->setHeaderData(DEAL_TYPE_COL, Qt::Horizontal, "Тип сделки");
    model->setHeaderData(DISTRICT_COL, Qt::Horizontal, "Район");
    model->setHeaderData(ADDRESS_COL, Qt::Horizontal, "Адрес");
    model->setHeaderData(DESCRIPTION_COL, Qt::Horizontal, "Описание");
    model->setHeaderData(SQUARE_COL, Qt::Horizontal, "Площадь, м^2");
    model->setHeaderData(FLOOR_AMOUNT_COL, Qt::Horizontal, "Кол-во комнат");
    model->setHeaderData(YEAR_COL, Qt::Horizontal, "Год постройки");
    model->setHeaderData(PRICE_COL, Qt::Horizontal, "Цена, USD");

    ui->tableView_estate->verticalHeader()->setVisible(false);
    ui->tableView_estate->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_estate->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_estate->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void RealEstateBase::on_tableView_estate_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}


void RealEstateBase::on_pushButton_delete_clicked()
{
    if (currentRow >= 0) {
        QModelIndex index;
        QVariant data;
        int ID;

        index = resModel->index(currentRow, ID_COL);
        data = resModel->data(index);
        ID = data.toInt();

        index = resModel->index(currentRow, PROPERTY_TYPE_COL);
        data = resModel->data(index);

        QSqlTableModel* extendedModel = new QSqlTableModel();
        if (data.toString() == APARTMENT_RUS) {
            extendedModel->setTable(APARTMENT_ENG);
            extendedModel->select();
        }
        else if (data.toString() == HOUSE_RUS) {
            extendedModel->setTable(HOUSE_ENG);
            extendedModel->select();
        }
        else if (data.toString() == OFFICE_RUS) {
            extendedModel->setTable(OFFICE_ENG);
            extendedModel->select();
        }
        else {
            delete extendedModel;
            return;
        }


        int rowToDeleteModel = findID(model, ID);
        int rowToDeleteExtendedModel = findID(extendedModel, ID);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle("Подтверждение удаления");
        msgBox.setText("Вы уверены, что хотите удалить этот объект?");
        msgBox.addButton(QMessageBox::Yes)->setText("Да");
        msgBox.addButton(QMessageBox::No)->setText("Нет");
        msgBox.setDefaultButton(QMessageBox::No);

        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            model->removeRow(rowToDeleteModel);
            extendedModel->removeRow(rowToDeleteExtendedModel);
            model->select();
            setFilters();
            QMessageBox::information(this, "Успех", "Объект успешно удален!");
        }
        delete extendedModel;
    }
    else {
        QMessageBox::warning(this, "Предупреждение", "Объект для удаления не выбран!");
    }

    ui->tableView_estate->clearSelection();
    currentRow = -1;
}

void RealEstateBase::on_pushButton_estate_clicked()
{
    QModelIndex index;
    QVariant data;
    if (currentRow >= 0) {

        index = resModel->index(currentRow, PROPERTY_TYPE_COL);

        data = resModel->data(index);


        if (data.toString() == APARTMENT_RUS) {
            QDialog* dialog = new QDialog(this);
            objectOverview* oo = new objectOverview(dialog, model, resModel, "Apartment", currentRow, access, userID);

            dialog->setModal(true);

            dialog->setWindowTitle("Карточка квартиры");

            if (access == "rieltor")
                dialog->setFixedSize(500, 400);
            else if (access == "client")
                dialog->setFixedSize(500, 360);

            oo->setParent(dialog);
            oo->show();

            dialog->exec();

            delete oo;

            setFilters();
        }
        else if (data.toString() == HOUSE_RUS) {
            QDialog* dialog = new QDialog(this);
            objectOverview* oo = new objectOverview(dialog, model, resModel, "House", currentRow, access, userID);

            dialog->setModal(true);
            dialog->setWindowTitle("Карточка частного дома");

            if (access == "rieltor")
                dialog->setFixedSize(500, 400);
            else if (access == "client")
                dialog->setFixedSize(500, 360);

            oo->setParent(dialog);
            oo->show();

            dialog->exec();

            delete oo;

            setFilters();
        }
        else if (data.toString() == OFFICE_RUS) {
            QDialog* dialog = new QDialog(this);
            objectOverview* oo = new objectOverview(dialog, model, resModel, "Office", currentRow, access, userID);

            dialog->setModal(true);
            dialog->setWindowTitle("Карточка офиса");

            if (access == "rieltor")
                dialog->setFixedSize(500, 400);
            else if (access == "client")
                dialog->setFixedSize(500, 360);

            oo->setParent(dialog);
            oo->show();

            dialog->exec();

            delete oo;

            setFilters();
        }
    }
    else {
        QMessageBox::warning(this, "Предупреждение", "Объект для показа карточки не выбран!");
    }

    ui->tableView_estate->clearSelection();
    currentRow = -1;
}


int RealEstateBase::findID(QAbstractItemModel* model, int ID) {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < model->rowCount(); row++) {
        index = model->index(row, ID_COL);
        data = model->data(index).toString();
        if (data.toInt() == ID)
            return row;
    }
    return -1;
}

int RealEstateBase::findIDTwoFields(QAbstractItemModel* model, int ID1, int ID2) {
    QModelIndex index;
    QVariant data;

    for (int row = 0; row < model->rowCount(); row++) {
        index = model->index(row, 0);
        data = model->data(index).toString();
        if (data.toInt() == ID1) {
            index = model->index(row, 1);
            data = model->data(index).toString();
            if (data.toInt() == ID2)
                return row;
        }
    }
    return -1;
}

void RealEstateBase::on_pushButton_add_clicked()
{
    QDialog* dialog = new QDialog(this);
    objectAdding* oa = new objectAdding(dialog, model);

    dialog->setModal(true);
    dialog->setWindowTitle("Добавление объекта");
    dialog->setFixedSize(300, 500);
    oa->setParent(dialog);

    oa->show();

    dialog->exec();

    delete oa;

    ui->tableView_estate->clearSelection();

    setFilters();
}

void RealEstateBase::on_comboBox_type_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_comboBox_district_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_comboBox_floor_amount_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_comboBox_deal_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    setFilters();
}

void RealEstateBase::on_pushButton_reject_clicked()
{
    if (currentRow >= 0) {
        QSqlTableModel* tempModel = new QSqlTableModel();
        tempModel->setTable(REQUESTS);
        tempModel->select();

        QModelIndex index;
        index = resModel->index(currentRow, ID_COL);
        int ID = resModel->data(index).toInt();

        int rowToReject = findID(tempModel, ID);

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle("Подтверждение отклонения");
        msgBox.setText("Вы уверены, что хотите отклонить эту заявку?");
        msgBox.addButton(QMessageBox::Yes)->setText("Да");
        msgBox.addButton(QMessageBox::No)->setText("Нет");
        msgBox.setDefaultButton(QMessageBox::No);

        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            tempModel->removeRow(rowToReject);
            tempModel->select();
            setFilters();
            QMessageBox::information(this, "Успех", "Заявка успешно отклонена!");
        }

        delete tempModel;

    }
    else {
        QMessageBox::warning(this, "Предупреждение", "Объект для отклонения заявки не выбран!");
    }
    ui->tableView_estate->clearSelection();
    currentRow = -1;
}

