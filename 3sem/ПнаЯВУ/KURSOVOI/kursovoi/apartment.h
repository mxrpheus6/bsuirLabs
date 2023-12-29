#ifndef APARTMENT_H
#define APARTMENT_H

#include "realestate.h"

class Apartment : public RealEstate
{
private:
    double squareKitchen;
    int allFloorsAmount;
    QString layoutType;
    QString hasBalcony;
    QString hasElevator;
    double ceilingHeight;
    QString hasParking;
    QString hasConcierge;
public:
    Apartment();
    //Apartment(const RealEstate& realEstate);

    void setSquareKitchen(double squareKitchen);
    double getSquareKitchen();

    void setAllFloorsAmount(int allFloorsAmount);
    int getAllFloorsAmount();

    void setLayoutType(QString layoutType);
    QString getLayoutType();

    void setHasBalcony(QString hasBalcony);
    QString getHasBalcony();

    void setHasElevator(QString hasElevator);
    QString getHasElevator();

    void setCeilingHeight(double ceilingHeight);
    double getCeilingHeight();

    void setHasParking(QString hasParking);
    QString getHasParking();

    void setHasConcierge(QString hasConcierge);
    QString getHasConcierge();
};

#endif // APARTMENT_H
