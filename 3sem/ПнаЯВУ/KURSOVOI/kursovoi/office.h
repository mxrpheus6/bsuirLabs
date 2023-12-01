#ifndef OFFICE_H
#define OFFICE_H

#include "realestate.h"

class Office : public RealEstate
{
private:
    QString officeClass;
    int allFloorsAmount;
    int workstationsAmount;
    QString wallMaterial;
    QString renovation;
    QString hasConferenceRooms;
    QString hasSecurityFeatures;
    QString hasToilet;

public:
    Office();
    Office(const RealEstate& realEstate);

    void setOfficeClass(QString officeClass);
    QString getOfficeClass();

    void setAllFloorsAmount(int allFloorsAmount);
    int getAllFloorsAmount();

    void setWorkstationsAmount(int workstationsAmount);
    int getWorkstationsAmount();

    void setWallMaterial(QString wallMaterial);
    QString getWallMaterial();

    void setRenovation(QString renovation);
    QString getRenovation();

    void setHasConferenceRooms(QString hasConferenceRooms);
    QString getHasConferenceRooms();

    void setHasSecurityFeatures(QString hasSecurityFeatures);
    QString getHasSecurityFeatures();

    void setHasToilet(QString hasToilet);
    QString getHasToilet();
};

#endif // OFFICE_H
