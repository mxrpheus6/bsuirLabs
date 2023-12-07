#include "menudatawidget.h"
#include "ui_menudatawidget.h"

MenuDataWidget::MenuDataWidget(QWidget *parent, QString access, QString tableName) :
    QWidget(parent),
    ui(new Ui::MenuDataWidget)
{
    ui->setupUi(this);

    model = new QSqlTableModel();
    model->setTable(tableName);

    if (access == "client" && tableName == ACCOUNTS) {
        model->setFilter("access = 'rieltor'");
    }

    model->select();

    if (tableName == ACCOUNTS) {
        model->setHeaderData(ID_COL, Qt::Horizontal, "ID");
        model->setHeaderData(NAME_COL, Qt::Horizontal, "ФИО");
        model->setHeaderData(LOGIN_COL, Qt::Horizontal, "Логин");
        model->setHeaderData(PASSWORD_COL, Qt::Horizontal, "Пароль");
        model->setHeaderData(PASSPORT_COL, Qt::Horizontal, "Паспорт");
        model->setHeaderData(PHONE_COL, Qt::Horizontal, "Телефон");
        model->setHeaderData(ACCESS_COL, Qt::Horizontal, "Права доступа");
        ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    else if (tableName == DISTRICTS) {
        model->setHeaderData(0, Qt::Horizontal, "Район");
        ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    ui->tableView_db->setModel(model);
    ui->tableView_db->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_db->verticalHeader()->setVisible(false);

    if (access == "client") {


        ui->pushButton_add->setEnabled(false);
        ui->pushButton_add->setVisible(false);
        ui->pushButton_del->setEnabled(false);
        ui->pushButton_del->setVisible(false);

        ui->tableView_db->setColumnHidden(LOGIN_COL, true);
        ui->tableView_db->setColumnHidden(PASSWORD_COL, true);
        ui->tableView_db->setColumnHidden(PASSPORT_COL, true);
        ui->tableView_db->setColumnHidden(ACCESS_COL, true);

        ui->tableView_db->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView_db->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
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
