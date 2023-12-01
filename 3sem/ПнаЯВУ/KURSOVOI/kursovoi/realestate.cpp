#include "realestate.h"

RealEstate::RealEstate()
{
    ID = 0;
    propertyType = "";
    dealType = "";
    district = "";
    address = "";
    description = "";
    square = 0.0;
    floorsAmount = 0;
    constructionYear = 0;
    price = 0.0;
}

void RealEstate::setID(int ID) {
    this->ID = ID;
}
int RealEstate::getID() {
    return ID;
}

void RealEstate::setPropertyType(QString propertyType) {
    this->propertyType = propertyType;
}
QString RealEstate::getPropertyType() {
    return propertyType;
}

void RealEstate::setDealType(QString dealType) {
    this->dealType = dealType;
}
QString RealEstate::getDealType() {
    return dealType;
}

void RealEstate::setDistrict(QString district) {
    this->district = district;
}
QString RealEstate::getDistrict() {
    return district;
}

void RealEstate::setAddress(QString address) {
    this->address = address;
}
QString RealEstate::getAddress() {
    return address;
}

void RealEstate::setDescription(QString description) {
    this->description = description;
}
QString RealEstate::getDescription() {
    return description;
}

void RealEstate::setSquare(double square) {
    if (square <= 0.0)
        throw QString("В поле площадь записано некорректное значение!");
    this->square = square;
}
double RealEstate::getSquare() {
    return square;
}

void RealEstate::setFloorsAmount(int floorsAmount) {
    if (floorsAmount <= 0)
        throw QString("В поле количество комнат записано некорректное значение!");
    this->floorsAmount = floorsAmount;
}
int RealEstate::getFloorsAmount() {
    return floorsAmount;
}

void RealEstate::setConstructionYear(int constructionYear) {
    if (constructionYear <= 0)
        throw QString("В поле год постройки записано некорректное значение!");
    this->constructionYear = constructionYear;
}
int RealEstate::getConstructionYear() {
    return constructionYear;
}

void RealEstate::setPrice(double price) {
    if (price <= 0.0)
        throw QString("В поле цена записано некорректное значение!");
    this->price = price;
}
double RealEstate::getPrice() {
    return price;
}
