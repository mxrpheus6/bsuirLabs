#include "office.h"

Office::Office() : RealEstate()
{
    officeClass = "";
    allFloorsAmount = 0;
    workstationsAmount = 0;
    wallMaterial = "";
    renovation = "";
    hasConferenceRooms = "";
    hasSecurityFeatures = "";
    hasToilet = "";
}

void Office::setOfficeClass(QString officeClass) {
    this->officeClass = officeClass;
}
QString Office::getOfficeClass() {
    return officeClass;
}

void Office::setAllFloorsAmount(int allFloorsAmount) {
    this->allFloorsAmount = allFloorsAmount;
}
int Office::getAllFloorsAmount() {
    return allFloorsAmount;
}

void Office::setWorkstationsAmount(int workstationsAmount) {
    this->workstationsAmount = workstationsAmount;
}
int Office::getWorkstationsAmount() {
    return workstationsAmount;
}

void Office::setWallMaterial(QString wallMaterial) {
    this->wallMaterial = wallMaterial;
}
QString Office::getWallMaterial() {
    return wallMaterial;
}

void Office::setRenovation(QString renovation) {
    this->renovation = renovation;
}
QString Office::getRenovation() {
    return renovation;
}

void Office::setHasConferenceRooms(QString hasConferenceRooms) {
    this->hasConferenceRooms = hasConferenceRooms;
}
QString Office::getHasConferenceRooms() {
    return hasConferenceRooms;
}

void Office::setHasSecurityFeatures(QString hasSecurityFeatures) {
    this->hasSecurityFeatures = hasSecurityFeatures;
}
QString Office::getHasSecurityFeatures() {
    return hasSecurityFeatures;
}

void Office::setHasToilet(QString hasToilet) {
    this->hasToilet = hasToilet;
}
QString Office::getHasToilet() {
    return hasToilet;
}
