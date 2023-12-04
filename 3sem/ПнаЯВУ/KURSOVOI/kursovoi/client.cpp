#include "client.h"

Client::Client()
{
    ID = 0;
    name = "";
    login = "";
    password = "";
    passport = "";
    phone = "";
    access = "client";
}

void Client::setID(int ID) {
    this->ID = ID;
}
int Client::getID() {
    return ID;
}

void Client::setName(QString name) {
    this->name = name;
}
QString Client::getName() {
    return name;
}

void Client::setLogin(QString login) {
    if (login.length() < 6)
        throw QString("Длина логина должна состоять из минимум 6 символов!");
    this->login = login;
}
QString Client::getLogin() {
    return login;
}

void Client::setPassword(QString password) {
    if (password.length() < 8)
        throw QString("Длина пароля должна состоять из минимум 8 символов!");
    this->password = password;
}
QString Client::getPassword() {
    return password;
}

void Client::setPassport(QString passport) {
    this->passport = passport;
}
QString Client::getPassport() {
    return passport;
}

void Client::setPhone(QString phone) {
    this->phone = phone;
}
QString Client::getPhone() {
    return phone;
}

void Client::setAccess(QString access) {
    if (access != "client" || access != "rieltor")
        throw QString("Неверные права доступа!");
    this->access = access;
}
QString Client::getAccess() {
    return access;
}
