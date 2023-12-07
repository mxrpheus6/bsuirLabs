#ifndef DEFINES_H
#define DEFINES_H

#define ACCOUNTS "Accounts"
#define DISTRICTS "Districts"
#define ESTATE "Estate"
#define DEALS "Deals"
#define REQUESTS "Requests"

/*#define ID_COL 0
#define PROPERTY_TYPE_COL 1
#define DEAL_TYPE_COL 2
#define DISTRICT_COL 3
#define ADDRESS_COL 4
#define DESCRIPTION_COL 5
#define SQUARE_COL 6
#define FLOOR_AMOUNT_COL 7
#define YEAR_COL 8
#define PRICE_COL 9*/

/*constexpr int ID_COL = 0;
//Таблица estate
constexpr int PROPERTY_TYPE_COL = 1;
constexpr int DEAL_TYPE_COL = 2;
constexpr int DISTRICT_COL = 3;
constexpr int ADDRESS_COL = 4;
constexpr int DESCRIPTION_COL = 5;
constexpr int SQUARE_COL = 6;
constexpr int FLOOR_AMOUNT_COL = 7;
constexpr int YEAR_COL = 8;
constexpr int PRICE_COL = 9;*/

/*
//таблица apartment
constexpr int APARTMENT_KITCHEN_COL = 1;
constexpr int APARTMENT_ALL_FLOORS_COL = 2;
constexpr int APARTMENT_LAYOUT_COL = 3;
constexpr int APARTMENT_BALCONY_COL = 4;
constexpr int APARTMENT_ELEVATOR_COL = 5;
constexpr int APARTMENT_CEILING_COL = 6;
constexpr int APARTMENT_PARKING_COL = 7;
constexpr int APARTMENT_CONCIERGE_COL = 8;

//таблица house
constexpr int HOUSE_LAND_COL = 1;
constexpr int HOUSE_KITCHEN_COL = 2;
constexpr int HOUSE_WALL_COL = 3;
constexpr int HOUSE_ROOF_COL = 4;
constexpr int HOUSE_FIREPLACE_COL = 5;
constexpr int HOUSE_GARAGE_COL = 6;
constexpr int HOUSE_HEATING_COL = 7;
constexpr int HOUSE_SANITATION_COL = 8;
constexpr int HOUSE_WATER_COL = 9;

//таблица office
constexpr int OFFICE_CLASS = 1;
constexpr int OFFICE_ALL_FLOORS_COL = 2;
constexpr int OFFICE_WORKSTATIONS_COL = 3;
constexpr int OFFICE_WALL_COL = 4;
constexpr int OFFICE_RENOVATION_COL = 5;
constexpr int OFFICE_CONFERENCE_COL = 6;
constexpr int OFFICE_SECURITY_COL = 7;
constexpr int OFFICE_TOILET_COL = 8;*/

/*
//таблциа accounts
constexpr int NAME_COL = 1;
constexpr int LOGIN_COL = 2;
constexpr int PASSWORD_COL = 3;
constexpr int PASSPORT_COL = 4;
constexpr int PHONE_COL = 5;
constexpr int ACCESS_COL = 6;*/

//таблица requests
constexpr int ID_CLIENT_REQ = 1;

//таблица deals
constexpr int ID_RIELTOR = 1;
constexpr int ID_CLIENT_DEAL = 2;

enum EstateСolumns {
    ID_COL = 0,
    PROPERTY_TYPE_COL = 1,
    DEAL_TYPE_COL = 2,
    DISTRICT_COL = 3,
    ADDRESS_COL = 4,
    DESCRIPTION_COL = 5,
    SQUARE_COL = 6,
    FLOOR_AMOUNT_COL = 7,
    YEAR_COL = 8,
    PRICE_COL = 9
};

enum ApartmentColumns {
    APARTMENT_KITCHEN_COL = 1,
    APARTMENT_ALL_FLOORS_COL = 2,
    APARTMENT_LAYOUT_COL = 3,
    APARTMENT_BALCONY_COL = 4,
    APARTMENT_ELEVATOR_COL = 5,
    APARTMENT_CEILING_COL = 6,
    APARTMENT_PARKING_COL = 7,
    APARTMENT_CONCIERGE_COL = 8
};

enum HouseColumns {
    HOUSE_LAND_COL = 1,
    HOUSE_KITCHEN_COL = 2,
    HOUSE_WALL_COL = 3,
    HOUSE_ROOF_COL = 4,
    HOUSE_FIREPLACE_COL = 5,
    HOUSE_GARAGE_COL = 6,
    HOUSE_HEATING_COL = 7,
    HOUSE_SANITATION_COL = 8,
    HOUSE_WATER_COL = 9
};

enum OfficeColumns {
    OFFICE_CLASS = 1,
    OFFICE_ALL_FLOORS_COL = 2,
    OFFICE_WORKSTATIONS_COL = 3,
    OFFICE_WALL_COL = 4,
    OFFICE_RENOVATION_COL = 5,
    OFFICE_CONFERENCE_COL = 6,
    OFFICE_SECURITY_COL = 7,
    OFFICE_TOILET_COL = 8
};

enum AccountsColumns {
    NAME_COL = 1,
    LOGIN_COL = 2,
    PASSWORD_COL = 3,
    PASSPORT_COL = 4,
    PHONE_COL = 5,
    ACCESS_COL = 6
};

#define APARTMENT_RUS "Квартира"
#define HOUSE_RUS "Дом"
#define OFFICE_RUS "Офис"

#define APARTMENT_ENG "Apartment"
#define HOUSE_ENG "House"
#define OFFICE_ENG "Office"

#define DEALS_ARR {"Продажа", "Аренда"}
#define PROPERTY_ARR {"Квартира", "Дом", "Офис"}


#endif  // DEFINES_H
