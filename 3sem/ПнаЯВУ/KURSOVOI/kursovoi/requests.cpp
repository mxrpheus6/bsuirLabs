#include "requests.h"
#include "ui_requests.h"

Requests::Requests(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Requests)
{
    ui->setupUi(this);

    model = new QSqlTableModel();
    model->setTable(REQUESTS);
    createEmptyTable(model);

    model->select();


    ui->tableView->setModel(model);
}

void Requests::createEmptyTable(QSqlTableModel* model) {
    model->setHeaderData(0, Qt::Horizontal, "ID Недвижимости");
    model->setHeaderData(1, Qt::Horizontal, "ID Риелтора");
    model->setHeaderData(2, Qt::Horizontal, "ID Клиента");
    model->setHeaderData(3, Qt::Horizontal, "Дата заявки");

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

Requests::~Requests()
{
    delete ui;
}
