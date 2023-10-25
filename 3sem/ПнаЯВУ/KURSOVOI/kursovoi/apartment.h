#ifndef APARTMENT_H
#define APARTMENT_H

#include "realestate.h"

class Apartment : public RealEstate
{
private:
    int rooms_amount;
    int floor;
    QString layout_type;
    bool has_balcony;
public:
    Apartment();

    void set_rooms_amount(int rooms_amount);
    int get_rooms_amount();

    void set_floor(int floor);
    int get_floor();

    void set_layout_type(QString layout_type);
    QString get_layout_type();

    void set_has_balcony(bool has_balcony);
    bool get_has_balcony();
};

#endif // APARTMENT_H
