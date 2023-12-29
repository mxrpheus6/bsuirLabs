#include "house.h"

/*House::House(const RealEstate& realEstate) : RealEstate(realEstate)
{
    landSquare = -1.0;
    kitchenSquare = -1.0;
    wallMaterial = "";
    roofMaterial = "";
    hasFireplace = "";
    hasGarage = "";
    heatingType = "";
    sanitation = "";
    waterSupply = "";
}*/

House::House() : RealEstate()
{
    landSquare = -1.0;
    kitchenSquare = -1.0;
    wallMaterial = "";
    roofMaterial = "";
    hasFireplace = "";
    hasGarage = "";
    heatingType = "";
    sanitation = "";
    waterSupply = "";
}

void House::setLandSquare(double landSquare) {
    if (landSquare <= 0.0)
        throw QString("В поле площадь участка записано некорректное значение!");
    this->landSquare = landSquare;
}
double House::getLandSquare() {
    return landSquare;
}

void House::setKitchenSquare(double kitchenSquare) {
    if (kitchenSquare <= 0.0)
        throw QString("В поле площадь кухни записано некорректное значение!");
    this->kitchenSquare = kitchenSquare;
}
double House::getKitchenSquare() {
    return kitchenSquare;
}

void House::setWallMaterial(QString wallMaterial) {
    this->wallMaterial = wallMaterial;
}
QString House::getWallMaterial() {
    return wallMaterial;
}

void House::setRoofMaterial(QString roofMaterial) {
    this->roofMaterial = roofMaterial;
}
QString House::getRoofMaterial() {
    return roofMaterial;
}

void House::setHasFireplace(QString hasFireplace) {
    this->hasFireplace = hasFireplace;
}
QString House::getHasFireplace() {
    return hasFireplace;
}

void House::setHasGarage(QString hasGarage) {
    this->hasGarage = hasGarage;
}
QString House::getHasGarage() {
    return hasGarage;
}

void House::setHeatingType(QString heatingType) {
    this->heatingType = heatingType;
}
QString House::getHeatingType() {
    return heatingType;
}

void House::setSanitation(QString sanitation) {
    this->sanitation = sanitation;
}
QString House::getSanitation() {
    return sanitation;
}

void House::setWaterSupply(QString waterSupply) {
    this->waterSupply = waterSupply;
}
QString House::getWaterSupply() {
    return waterSupply;
}
