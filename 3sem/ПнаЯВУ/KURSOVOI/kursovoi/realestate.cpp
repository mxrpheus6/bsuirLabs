#include "realestate.h"

RealEstate::RealEstate()
{
    square = 0.0;
    floors_amount = 0;
    property_type = "";
    description = "";
    district = "";
    address = "";
    construction_year = 0;
}

void RealEstate::set_square(double square) {
    this->square = square;
}
double RealEstate::get_square() {
    return square;
}

void RealEstate::set_floors_amount(int floors_amount) {
    this->floors_amount = floors_amount;
}
int RealEstate::get_floors_amount() {
    return floors_amount;
}

void RealEstate::set_property_type(QString property_type) {
    this->property_type = property_type;
}
QString RealEstate::get_property_type() {
    return property_type;
}

void RealEstate::set_description(QString description) {
    this->description = description;
}
QString RealEstate::get_description() {
    return description;
}

void RealEstate::set_district(QString district) {
    this->district = district;
}
QString RealEstate::get_district() {
    return district;
}

void RealEstate::set_address(QString address) {
    this->address = address;
}
QString RealEstate::get_address() {
    return address;
}

void RealEstate::set_construction_year(int construction_year) {
    this->construction_year = construction_year;
}
int RealEstate::get_construction_year() {
    return construction_year;
}

void RealEstate::set_price(double price) {
    this->square = square;
}
double RealEstate::get_price() {
    return square;
}
