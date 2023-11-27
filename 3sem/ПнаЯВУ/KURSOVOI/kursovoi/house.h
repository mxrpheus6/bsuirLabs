#ifndef HOUSE_H
#define HOUSE_H

#include "realestate.h"

class House : public RealEstate
{
private:
    double landSquare;
    double kitchenSquare;
    QString wallMaterial;
    QString roofMaterial;
    QString hasGarage;
    QString heatingType;
    QString sanitation;
    QString waterSupply;

public:
    House();

    void setLandSquare(double landSquare);
    double getLandSquare();

    void setKitchenSquare(double kitchenSquare);
    double getKitchenSquare();

    void setWallMaterial(QString wallMaterial);
    QString getWallMaterial();

    void setRoofMaterial(QString roofMaterial);
    QString getRoofMaterial();

    void setHasGarage(QString hasGarage);
    QString getHasGarage();

    void setHeatingType(QString heatingType);
    QString getHeatingType();

    void setSanitation(QString sanitation);
    QString getSanitation();

    void setWaterSupply(QString waterSupply);
    QString getWaterSupply();
};

#endif // HOUSE_H
