#include "DataStructures.h"

UserInfo::UserInfo(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    type = record.value("type").toInt();
    discount = record.value("discount").toInt();

    setNameFromBase(record.value("name").toString());
    passportSeries = record.value("passport_series").toString();
    passportNumber = record.value("passport_number").toString();
    issuedOrganize = record.value("issued_organize").toString();
    registration = record.value("registration").toString();
    cardNumber = record.value("card_number").toString();
}

void UserInfo::setNameFromBase(const QString &name)
{
    QStringList names = name.split("##");
    int count = names.count();

    if (count > 0)
    {
        firstName = names.at(0);
    }

    if (count > 1)
    {
        middleName = names.at(1);
    }

    if (count > 2)
    {
        lastName = names.at(2);
    }
}

Genre::Genre(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    name = record.value("name").toString();
}

Publishing::Publishing(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    name = record.value("name").toString();
}

Author::Author(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    firstName = record.value("first_name").toString();
    middleName = record.value("middle_name").toString();
    lastName = record.value("last_name").toString();

    setName();
}

void Author::setName()
{
    if (!firstName.isEmpty())
    {
        name = firstName;
    }

    if (!name.isEmpty() && !middleName.isEmpty())
    {
        name = QString("%1 %2").arg(name).arg(middleName);
    }
    else if (!middleName.isEmpty())
    {
        name = middleName;
    }

    if (!name.isEmpty() && !lastName.isEmpty())
    {
        name = QString("%1 %2").arg(name).arg(lastName);
    }
    else if (!lastName.isEmpty())
    {
        name = lastName;
    }
}

Book::Book()
{

}

Book::Book(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    allCount = record.value("all_count").toInt();
    currentCount = record.value("current_count").toInt();

    name = record.value("name").toString();
    setDataList(record.value("genres").toString(), genres);
    publishing = record.value("publishing").toString();
    setDataList(record.value("authors").toString(), authors);
}

void Book::setDataList(const QString &data, QStringList &list)
{
    if (data.isEmpty())
    {
        return;
    }

    list = data.split("##");

    if (list.last().isEmpty())
    {
        list.removeLast();
    }
}
