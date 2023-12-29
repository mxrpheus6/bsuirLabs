#include "apartment.h"

Apartment::Apartment() : RealEstate()
{
    squareKitchen = -1.0;
    allFloorsAmount = -1;
    layoutType = "";
    hasBalcony = "";
    hasElevator = "";
    ceilingHeight = -1.0;
    hasParking = "";
    hasConcierge = "";
}

void Apartment::setSquareKitchen(double squareKitchen) {
    if (squareKitchen <= 0.0)
        throw QString("В поле площадь кухни записано некорректное значение!");
    this->squareKitchen = squareKitchen;
}
double Apartment::getSquareKitchen() {
    return squareKitchen;
}

void Apartment::setAllFloorsAmount(int allFloorsAmount) {
    if (allFloorsAmount <= 0)
        throw QString("В поле этажность записано некорректное значение!");
    this->allFloorsAmount = allFloorsAmount;
}
int Apartment::getAllFloorsAmount() {
    return allFloorsAmount;
}

void Apartment::setLayoutType(QString layoutType) {
    this->layoutType = layoutType;
}
QString Apartment::getLayoutType() {
    return layoutType;
}

void Apartment::setHasBalcony(QString hasBalcony) {
    this->hasBalcony = hasBalcony;
}
QString Apartment::getHasBalcony() {
    return hasBalcony;
}

void Apartment::setHasElevator(QString hasElevator) {
    this->hasElevator = hasElevator;
}
QString Apartment::getHasElevator() {
    return hasElevator;
}

void Apartment::setCeilingHeight(double ceilingHeight) {
    if (ceilingHeight <= 0.0)
        throw QString("В поле высота потолков записано некорректное значение!");
    this->ceilingHeight = ceilingHeight;
}
double Apartment::getCeilingHeight() {
    return ceilingHeight;
}

void Apartment::setHasParking(QString hasParking) {
    this->hasParking = hasParking;
}
QString Apartment::getHasParking() {
    return hasParking;
}

void Apartment::setHasConcierge(QString hasConcierge) {
    this->hasConcierge = hasConcierge;
}
QString Apartment::getHasConcierge() {
    return hasConcierge;
}
