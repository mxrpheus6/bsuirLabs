#include "makedeal.h"
#include "ui_makedeal.h"

MakeDeal::MakeDeal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeDeal)
{
    ui->setupUi(this);
}

MakeDeal::~MakeDeal()
{
    delete ui;
}
