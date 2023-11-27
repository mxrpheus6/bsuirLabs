#ifndef REALESTATE_H
#define REALESTATE_H

#include <QString>

class RealEstate
{
private:
    int ID;
    QString propertyType;
    QString dealType;
    QString district;
    QString address;
    QString description;
    double square;
    int floorsAmount;
    int constructionYear;
    double price;

public:
    RealEstate();

    void setID(int ID);
    int getID();

    void setPropertyType(QString propertyType);
    QString getPropertyType();

    void setDealType(QString dealType);
    QString getDealType();

    void setDistrict(QString district);
    QString getDistrict();

    void setAddress(QString address);
    QString getAddress();

    void setDescription(QString description);
    QString getDescription();

    void setSquare(double square);
    double getSquare();

    void setFloorsAmount(int floorsAmount);
    int getFloorsAmount();

    void setConstructionYear(int constructionYear);
    int getConstructionYear();

    void setPrice(double price);
    double getPrice();
};

#endif // REALESTATE_H
