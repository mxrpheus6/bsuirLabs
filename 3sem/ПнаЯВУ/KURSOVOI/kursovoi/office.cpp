#include "office.h"

Office::Office()
{
    workstations_amount = 0;
    office_layout = "";
    has_conference_rooms = false;
    has_security_features = false;
}

void Office::set_workstations_amount(int workstations_amount) {
    this->workstations_amount = workstations_amount;
}
int Office::get_workstations_amount() {
    return workstations_amount;
}

void Office::set_office_layout(QString office_layout) {
    this->office_layout = office_layout;
}
QString Office::get_office_layout() {
    return office_layout;
}

void Office::set_has_conference_rooms(bool has_conference_rooms) {
    this->has_conference_rooms = has_conference_rooms;
}
bool Office::get_has_conference_rooms() {
    return has_conference_rooms;
}

void Office::set_has_security_features(bool has_security_features) {
    this->has_security_features = has_security_features;
}
bool Office::get_has_security_features() {
    return has_security_features;
}
