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

    ui->tableView_db->setModel(model);
    ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_db->setColumnHidden(0, true);
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


void MenuDataWidget::on_pushButtonAdd_clicked()
{

}

