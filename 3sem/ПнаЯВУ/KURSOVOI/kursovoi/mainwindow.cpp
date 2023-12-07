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

void MainWindow::handleAuthorizationSuccessWithAccess(QString access, int ID) {
    this->access = access;
    userID = ID;

    if (access == "client") {
        ui->pushButton_real_estate_base->resize(621, 201);

        ui->pushButton_deals->setEnabled(false);
        ui->pushButton_deals->setVisible(false);
        ui->pushButton_real_estate_applications->setEnabled(false);
        ui->pushButton_real_estate_applications->setVisible(false);
    }
}

void MainWindow::on_action_realtors_triggered()
{
    QDialog* dialog = new QDialog(this);
    MenuDataWidget* mw = new MenuDataWidget(dialog, access, ACCOUNTS);
    dialog->setModal(true);

    if (access == "client")
        dialog->setWindowTitle("Риелторы");
    else if(access == "rieltor")
        dialog->setWindowTitle("Риелторы и клиенты");

    dialog->setFixedSize(400, 300);
    mw->setParent(dialog);
    mw->show();

    dialog->exec();

    delete mw;
}


void MainWindow::on_action_districts_triggered()
{
    QDialog* dialog = new QDialog(this);
    MenuDataWidget* mw = new MenuDataWidget(dialog, access, DISTRICTS);
    dialog->setModal(true);
    dialog->setWindowTitle("Районы");
    dialog->setFixedSize(400, 300);
    mw->setParent(dialog);
    mw->show();

    dialog->exec();

    delete mw;
}

void MainWindow::on_pushButton_real_estate_base_clicked()
{
    QDialog* dialog = new QDialog(this);
    RealEstateBase* reb = new RealEstateBase(dialog, "base", access, userID);
    dialog->setModal(true);
    dialog->setWindowTitle("База недвижимости");
    dialog->setFixedSize(550, 450);
    reb->setParent(dialog);
    reb->show();

    dialog->exec();

    delete reb;
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

    delete req;
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

    delete pur;
}

