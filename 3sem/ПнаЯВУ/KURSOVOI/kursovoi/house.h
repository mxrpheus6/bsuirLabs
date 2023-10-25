#ifndef HOUSE_H
#define HOUSE_H

#include "realestate.h"

class House : public RealEstate
{
private:
    double land_square;
    int floors_count;
    bool has_garage;
    QString heating_type;

public:
    House();

    void set_land_square(double land_square);
    double get_land_square();

    void set_floors_count(int floors_count);
    double get_floors_count();

    void set_has_garage(bool has_garage);
    bool get_has_garage();

    void set_heating_type(QString heating_type);
    QString get_heating_type();
};

#endif // HOUSE_H
