#ifndef client_H
#define client_H

#include <QString>

class Client
{
public:
    Client();

    void setID(int ID);
    int getID();

    void setName(QString name);
    QString getName();

    void setLogin(QString login);
    QString getLogin();

    void setPassword(QString password);
    QString getPassword();

    void setPassport(QString passport);
    QString getPassport();

    void setPhone(QString phone);
    QString getPhone();

    void setAccess(QString access);
    QString getAccess();
private:
    int ID;
    QString name;
    QString login;
    QString password;
    QString passport;
    QString phone;
    QString access;
};

#endif // client_H
