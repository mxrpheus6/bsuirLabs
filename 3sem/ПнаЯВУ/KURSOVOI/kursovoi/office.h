#ifndef OFFICE_H
#define OFFICE_H

#include "realestate.h"

class Office : public RealEstate
{
private:
    int workstations_amount;
    QString office_layout;
    bool has_conference_rooms;
    bool has_security_features;
public:
    Office();

    void set_workstations_amount(int workstations_amount);
    int get_workstations_amount();

    void set_office_layout(QString office_layout);
    QString get_office_layout();

    void set_has_conference_rooms(bool has_conference_rooms);
    bool get_has_conference_rooms();

    void set_has_security_features(bool has_security_features);
    bool get_has_security_features();
};

#endif // OFFICE_H
