#include "realestatebase.h"
#include "ui_realestatebase.h"

RealEstateBase::RealEstateBase(QWidget *parent, QString tableName) :
    QWidget(parent),
    ui(new Ui::RealEstateBase)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable(tableName);
    createEmptyTable(model);

    model->select();

    resModel = model;

    ui->tableView_estate->setModel(model);

    QStringList uniqueValues;
    QModelIndex index;
    QVariant value;

    //заполнение combobox
    for (int row = 0; row < model->rowCount(); ++row) {
        index = model->index(row, 1);
        value = model->data(index);
        if (!uniqueValues.contains(value.toString())) {
            uniqueValues << value.toString();
        }
    }

    ui->comboBox_type->addItems(uniqueValues);
    uniqueValues.clear();

    for (int row = 0; row < model->rowCount(); ++row) {
        index = model->index(row, 2);
        value = model->data(index);
        if (!uniqueValues.contains(value.toString())) {
            uniqueValues << value.toString();
        }
    }

    ui->comboBox_district->addItems(uniqueValues);
    uniqueValues.clear();

    for (int row = 0; row < model->rowCount(); ++row) {
        index = model->index(row, 6);
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
    ui->comboBox_district->setEnabled(false);
    ui->comboBox_floor_amount->setEnabled(false);

    //помещение в combobox placeholder
    ui->comboBox_type->setCurrentIndex(-1);
    ui->comboBox_district->setCurrentIndex(-1);
    ui->comboBox_floor_amount->setCurrentIndex(-1);

    doubleValidator = new QDoubleValidator();
    intValidator = new QIntValidator();

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
}

RealEstateBase::~RealEstateBase()
{
    delete ui;
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
        ui->tableView_estate->setModel(model);
        ui->comboBox_type->setEnabled(false);
        ui->comboBox_type->setCurrentIndex(-1);
        set_filters();
    }
}


void RealEstateBase::on_checkBox_district_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_district->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(model);
        ui->comboBox_district->setEnabled(false);
        ui->comboBox_district->setCurrentIndex(-1);
        set_filters();
    }
}


void RealEstateBase::on_checkBox_floor_amount_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->comboBox_floor_amount->setEnabled(true);
    }
    else {
        ui->tableView_estate->setModel(model);
        ui->comboBox_floor_amount->setEnabled(false);
        ui->comboBox_floor_amount->setCurrentIndex(-1);
        set_filters();
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

        ui->tableView_estate->setModel(model);
        ui->lineEdit_square_from->setEnabled(false);
        ui->lineEdit_square_to->setEnabled(false);
        set_filters();
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

        ui->tableView_estate->setModel(model);
        ui->lineEdit_year_from->setEnabled(false);
        ui->lineEdit_year_to->setEnabled(false);
        set_filters();
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

        ui->tableView_estate->setModel(model);
        ui->lineEdit_price_from->setEnabled(false);
        ui->lineEdit_price_to->setEnabled(false);
        set_filters();
    }
}


QStandardItemModel* RealEstateBase::apply_filter_combobox(QAbstractItemModel *originalModel, int colIndex, QComboBox *cb)
{
    QStandardItemModel *newModel = new QStandardItemModel(this);
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
    }
    return newModel;
}

QStandardItemModel* RealEstateBase::apply_filter_line_edit(QAbstractItemModel *originalModel, int colIndex, QLineEdit *from, QLineEdit *to)
{
    QStandardItemModel *newModel = new QStandardItemModel(this);
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

void RealEstateBase::set_filters() {
    resModel = model;

    if (ui->comboBox_type->currentIndex() != -1) {
        resModel= apply_filter_combobox(resModel, 1, ui->comboBox_type);
    }
    if (ui->comboBox_district->currentIndex() != -1) {
        resModel= apply_filter_combobox(resModel, 2, ui->comboBox_district);
    }
    if (!ui->lineEdit_square_to->text().isEmpty() || !ui->lineEdit_square_from->text().isEmpty()) {
        resModel= apply_filter_line_edit(resModel, 5, ui->lineEdit_square_from, ui->lineEdit_square_to);
    }
    if (!ui->lineEdit_year_to->text().isEmpty() || !ui->lineEdit_year_from->text().isEmpty()) {
        resModel= apply_filter_line_edit(resModel, 7, ui->lineEdit_year_from, ui->lineEdit_year_to);
    }
    if (!ui->lineEdit_price_to->text().isEmpty() || !ui->lineEdit_price_from->text().isEmpty()) {
        resModel= apply_filter_line_edit(resModel, 8, ui->lineEdit_price_from, ui->lineEdit_price_to);
    }
    if (ui->comboBox_floor_amount->currentIndex() != -1) {
        resModel= apply_filter_combobox(resModel, 6, ui->comboBox_floor_amount);
    }
    ui->tableView_estate->setModel(resModel);
}

//устанавливаем фильтры на comboBox
void RealEstateBase::on_comboBox_type_activated(int index)
{
    Q_UNUSED(index);
    set_filters();
}

void RealEstateBase::on_comboBox_district_activated(int index)
{
    Q_UNUSED(index);
    set_filters();

}

void RealEstateBase::on_comboBox_floor_amount_activated(int index)
{
    Q_UNUSED(index);
    set_filters();
}

//устанавливаем фильтры на lineEdit
void RealEstateBase::on_lineEdit_square_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}

void RealEstateBase::on_lineEdit_square_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}

void RealEstateBase::on_lineEdit_year_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}


void RealEstateBase::on_lineEdit_year_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}

void RealEstateBase::on_lineEdit_price_from_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}


void RealEstateBase::on_lineEdit_price_to_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    set_filters();
}

void RealEstateBase::createEmptyTable(QSqlTableModel* model) {
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Тип");
    model->setHeaderData(2, Qt::Horizontal, "Район");
    model->setHeaderData(3, Qt::Horizontal, "Адрес");
    model->setHeaderData(4, Qt::Horizontal, "Описание");
    model->setHeaderData(5, Qt::Horizontal, "Площадь, м^2");
    model->setHeaderData(6, Qt::Horizontal, "Кол-во комнат");
    model->setHeaderData(7, Qt::Horizontal, "Год постройки");
    model->setHeaderData(8, Qt::Horizontal, "Цена, USD");

    ui->tableView_estate->verticalHeader()->setVisible(false);

    ui->tableView_estate->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_estate->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_estate->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_estate->setSortingEnabled(true);
}
