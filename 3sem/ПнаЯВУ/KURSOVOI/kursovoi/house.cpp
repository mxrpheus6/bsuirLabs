#include "house.h"

House::House()
{
    land_square = 0.0;
    floors_count = 0;
    has_garage = false;
    heating_type = "";
}

void House::set_land_square(double land_square) {
    this->land_square = land_square;
}
double House::get_land_square() {
    return land_square;
}

void House::set_floors_count(int floors_count) {
    this->floors_count = floors_count;
}
double House::get_floors_count() {
    return floors_count;
}

void House::set_has_garage(bool has_garage) {
    this->has_garage = has_garage;
}
bool House::get_has_garage() {
    return has_garage;
}

void House::set_heating_type(QString heating_type) {
    this->heating_type = heating_type;
}
QString House::get_heating_type() {
    return heating_type;
}
