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

struct BaseDataInfo
{
    qlonglong id;

    QString name;
};

struct Genre : public BaseDataInfo
{
    Genre(const QSqlRecord &record);
};

struct Publishing : public BaseDataInfo
{
    Publishing(const QSqlRecord &record);
};

struct Author : public BaseDataInfo
{
    QString firstName;
    QString lastName;
    QString middleName;

    Author(const QSqlRecord &record);

    void setName();
};

struct Book : public BaseDataInfo
{
    int allCount;
    int currentCount;

    QStringList genres;
    QString publishing;
    QStringList authors;

    Book();
    Book(const QSqlRecord &record);

    void setDataList(const QString &data, QStringList &list);
};

typedef QList<std::shared_ptr<BaseDataInfo>> BaseDataInfos;
typedef QList<std::shared_ptr<Genre>> Genres;
typedef QList<std::shared_ptr<Publishing>> Publishings;
typedef QList<std::shared_ptr<Author>> Authors;
typedef QList<std::shared_ptr<Book>> Books;

#endif // DATASTRUCTURES_H
