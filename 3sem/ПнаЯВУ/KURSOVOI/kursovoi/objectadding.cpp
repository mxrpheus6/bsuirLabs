#include "objectadding.h"
#include "ui_objectadding.h"

objectAdding::objectAdding(QWidget *parent, QSqlTableModel* originalModel) :
    QWidget(parent),
    ui(new Ui::objectAdding)
{
    ui->setupUi(this);

    ui->comboBox_deal->setCurrentIndex(-1);
    ui->comboBox_district->setCurrentIndex(-1);
    ui->comboBox_type->setCurrentIndex(-1);

    ui->lineEdit_ID->setEnabled(false);

    QDoubleValidator* doubleValidator = new QDoubleValidator();
    QIntValidator* intValidator = new QIntValidator();
    ui->lineEdit_floor_amount->setValidator(intValidator);
    ui->lineEdit_year->setValidator(intValidator);
    ui->lineEdit_price->setValidator(doubleValidator);
    ui->lineEdit_square->setValidator(doubleValidator);

    model = originalModel;

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

}

objectAdding::~objectAdding()
{
    delete ui;
}

