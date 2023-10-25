#include "realestatebase.h"
#include "ui_realestatebase.h"

RealEstateBase::RealEstateBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealEstateBase)
{
    ui->setupUi(this);
}

RealEstateBase::~RealEstateBase()
{
    delete ui;
}
