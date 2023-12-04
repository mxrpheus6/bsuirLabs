#include "menudatawidget.h"
#include "ui_menudatawidget.h"

MenuDataWidget::MenuDataWidget(QWidget *parent, QString tableName) :
    QWidget(parent),
    ui(new Ui::MenuDataWidget)
{
    ui->setupUi(this);

    model = new QSqlTableModel();
    model->setTable(tableName);
    model->select();

    if (tableName == ACCOUNTS) {
        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "ФИО");
        model->setHeaderData(2, Qt::Horizontal, "Логин");
        model->setHeaderData(3, Qt::Horizontal, "Пароль");
        model->setHeaderData(4, Qt::Horizontal, "Паспорт");
        model->setHeaderData(5, Qt::Horizontal, "Телефон");
        model->setHeaderData(6, Qt::Horizontal, "Права доступа");
        ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    else if (tableName == DISTRICTS) {
        model->setHeaderData(0, Qt::Horizontal, "Район");
        ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    ui->tableView_db->setModel(model);
    ui->tableView_db->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_db->verticalHeader()->setVisible(false);
}

MenuDataWidget::~MenuDataWidget()
{
    delete ui;

    delete model;
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
