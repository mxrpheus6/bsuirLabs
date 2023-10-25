#include "apartment.h"

Apartment::Apartment()
{
    rooms_amount = 0;
    floor = 0;
    layout_type = "";
    has_balcony = false;
}

void Apartment::set_rooms_amount(int rooms_amount) {
    this->rooms_amount = rooms_amount;
}
int Apartment::get_rooms_amount() {
    return rooms_amount;
}

void Apartment::set_floor(int floor) {
    this->floor = floor;
}
int Apartment::get_floor() {
    return floor;
}

void Apartment::set_layout_type(QString layout_type) {
    this->layout_type = layout_type;
}
QString Apartment::get_layout_type() {
    return layout_type;
}

void Apartment::set_has_balcony(bool has_balcony) {
    this->has_balcony = has_balcony;
}
bool Apartment::get_has_balcony() {
    return has_balcony;
}
