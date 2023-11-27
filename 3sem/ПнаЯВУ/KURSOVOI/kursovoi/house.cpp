#include "house.h"

House::House() : RealEstate()
{
    landSquare = 0.0;
    kitchenSquare = 0.0;
    wallMaterial = "";
    roofMaterial = "";
    hasGarage = "";
    heatingType = "";
    sanitation = "";
    waterSupply = "";
}

void House::setLandSquare(double landSquare) {
    this->landSquare = landSquare;
}
double House::getLandSquare() {
    return landSquare;
}

void House::setKitchenSquare(double kitchenSquare) {
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
