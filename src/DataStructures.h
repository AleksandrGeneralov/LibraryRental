#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QObject>
#include <QtGlobal>

class UserInfo
{
    qlonglong id;
    int type;

    QString firstName;
    QString lastName;
    QString middleName;
    QString passportSeries;
    QString passportNumber;
    QString issuedOrganize;
    QString registration;
    QString cardNumber;
    int discount;

public:
    UserInfo();
};

#endif // DATASTRUCTURES_H
