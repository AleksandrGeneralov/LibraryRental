#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QObject>
#include <QtGlobal>
#include <QSqlRecord>
#include <QVariant>

#include "MainIncludes.h"

struct UserInfo
{
    qlonglong id;

    int type;
    int discount;

    QString firstName;
    QString lastName;
    QString middleName;
    QString passportSeries;
    QString passportNumber;
    QString issuedOrganize;
    QString registration;
    QString cardNumber;

    UserInfo(const QSqlRecord &record);

    void setNameFromBase(const QString &name);
};

struct Genre
{
    qlonglong id;

    QString name;

    Genre(const QSqlRecord &record);
};

struct Publishing
{
    qlonglong id;

    QString name;

    Publishing(const QSqlRecord &record);
};

struct Author
{
    qlonglong id;

    QString firstName;
    QString lastName;
    QString middleName;

    Author(const QSqlRecord &record);
};

struct Book
{
    qlonglong id;

    int allCount;
    int currentCount;

    QString name;
    QStringList genres;
    QString publishing;
    QStringList authors;

    Book(const QSqlRecord &record);

    void setDataList(const QString &data, QStringList &list);
};


typedef QList<std::unique_ptr<Genre>> Genres;
typedef QList<std::unique_ptr<Publishing>> Publishings;
typedef QList<std::unique_ptr<Author>> Authors;
typedef QList<std::shared_ptr<Book>> Books;

#endif // DATASTRUCTURES_H
