#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./db/real_estate.db");

    QPixmap pix("./img/banner.png");
    int width = ui->label_banner->width();
    int height = ui->label_banner->height();
    ui->label_banner->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::on_action_realtors_triggered()
{
    QDialog* dialog = new QDialog(this);
    MenuDataWidget* mw = new MenuDataWidget(dialog, ACCOUNTS);
    dialog->setModal(true);
    dialog->setWindowTitle("Риелторы");
    dialog->setFixedSize(400, 300);
    mw->setParent(dialog);
    mw->show();

    dialog->exec();
}


void MainWindow::on_action_districts_triggered()
{
    QDialog* dialog = new QDialog(this);
    MenuDataWidget* mw = new MenuDataWidget(dialog, DISTRICTS);
    dialog->setModal(true);
    dialog->setWindowTitle("Районы");
    dialog->setFixedSize(400, 300);
    mw->setParent(dialog);
    mw->show();

    dialog->exec();
}

void MainWindow::on_pushButton_real_estate_base_clicked()
{
    QDialog* dialog = new QDialog(this);
    RealEstateBase* reb = new RealEstateBase(dialog, "base");
    dialog->setModal(true);
    dialog->setWindowTitle("База недвижимости");
    dialog->setFixedSize(550, 450);
    reb->setParent(dialog);
    reb->show();

    dialog->exec();
}


void MainWindow::on_pushButton_real_estate_applications_clicked()
{
    QDialog* dialog = new QDialog(this);
    RealEstateBase* req = new RealEstateBase(dialog, "deals");
    dialog->setModal(true);
    dialog->setWindowTitle("Заявки на сделку");
    dialog->setFixedSize(550, 450);
    req->setParent(dialog);
    req->show();

    dialog->exec();
}


void MainWindow::on_pushButton_deals_clicked()
{
    QDialog* dialog = new QDialog(this);
    RealEstateBase* pur = new RealEstateBase(dialog, "purchases");
    dialog->setModal(true);
    dialog->setWindowTitle("Заключенные сделки");
    dialog->setFixedSize(550, 450);
    pur->setParent(dialog);
    pur->show();

    dialog->exec();
}

