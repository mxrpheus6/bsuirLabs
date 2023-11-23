#include "menudatawidget.h"
#include "ui_menudatawidget.h"

MenuDataWidget::MenuDataWidget(QWidget *parent, QString tableName) :
    QWidget(parent),
    ui(new Ui::MenuDataWidget)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->select();

    if (tableName == "Accounts") {
        model->setHeaderData(0, Qt::Horizontal, "ФИО");
        model->setHeaderData(1, Qt::Horizontal, "Логин");
        model->setHeaderData(2, Qt::Horizontal, "Пароль");
        model->setHeaderData(3, Qt::Horizontal, "Права доступа");
    }
    else if (tableName == "Districts") {
        model->setHeaderData(0, Qt::Horizontal, "Район");
    }

    ui->tableView_db->setModel(model);
    ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_db->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_db->setSortingEnabled(true);
}

MenuDataWidget::~MenuDataWidget()
{
    delete ui;
}

void MenuDataWidget::on_pushButton_add_clicked()
{
    model->insertRow(model->rowCount());
}


void MenuDataWidget::on_pushButton_del_clicked()
{
    model->removeRow(currentRow);
    model->select();
}


void MenuDataWidget::on_tableView_db_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}
