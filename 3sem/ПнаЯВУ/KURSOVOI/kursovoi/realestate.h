#ifndef REALESTATE_H
#define REALESTATE_H

#include <QString>

class RealEstate
{
private:
    double square;
    int floors_amount;
    QString property_type;
    QString description;
    QString district;
    QString address;
    int construction_year;
    double price;

public:
    RealEstate();

    void set_square(double square);
    double get_square();

    void set_floors_amount(int floors_amount);
    int get_floors_amount();

    void set_property_type(QString property_type);
    QString get_property_type();

    void set_description(QString description);
    QString get_description();

    void set_district(QString district);
    QString get_district();

    void set_address(QString address);
    QString get_address();

    void set_construction_year(int construction_year);
    int get_construction_year();

    void set_price(double price);
    double get_price();
};

#endif // REALESTATE_H
