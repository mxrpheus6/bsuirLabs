#include "apartment.h"

Apartment::Apartment() : RealEstate()
{
    squareKitchen = 0.0;
    allFloorsAmount = 0;
    layoutType = "";
    hasBalcony = "";
    hasElevator = "";
    ceilingHeight = 0.0;
    hasParking = "";
    hasConcierge = "";
}

void Apartment::setSquareKitchen(double squareKitchen) {
    this->squareKitchen = squareKitchen;
}
double Apartment::getSquareKitchen() {
    return squareKitchen;
}

void Apartment::setAllFloorsAmount(int allFloorsAmount) {
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

void Apartment::setCeilingHeight(int ceilingHeight) {
    this->ceilingHeight = ceilingHeight;
}
int Apartment::getCeilingHeight() {
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
