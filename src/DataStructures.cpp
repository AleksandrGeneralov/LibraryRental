#include "DataStructures.h"

UserInfo::UserInfo()
{
    userId = 0;

    type = 0;
    discount = 0;

    firstName = "";
    lastName = "";
    middleName = "";
    passportSeries = "";
    passportNumber = "";
    issuedOrganize = "";
    registration = "";
    cardNumber = "";
}

UserInfo::UserInfo(const QSqlRecord &record)
{
    userId = record.value("id").toLongLong();

    type = record.value("type").toInt();
    discount = record.value("discount").toInt();

    setNameFromBase(record.value("name").toString());
    passportSeries = record.value("passport_series").toString();
    passportNumber = record.value("passport_number").toString();
    issuedOrganize = record.value("issued_organize").toString();
    registration = record.value("registration").toString();
    cardNumber = record.value("card_number").toString();
}

void UserInfo::fillSqlData(QStringList &fields, QVariantList &values)
{
    fields << "user_id"; values << userId;
    fields << "type"; values << type;
    fields << "name"; values << QString("%1##%2##%3").arg(firstName).arg(middleName).arg(lastName);
    fields << "passport_series"; values << passportSeries;
    fields << "passport_number"; values << passportNumber;
    fields << "issued_organize"; values << issuedOrganize;
    fields << "registration"; values << registration;
    fields << "card_number"; values << cardNumber;
    fields << "discount"; values << discount;
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

void UserInfo::setCardNumber()
{
    cardNumber = createCardNumber();
}

QString UserInfo::createCardNumber()
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QString command = QString("SELECT card_number FROM users_info ORDER BY card_number DESC LIMIT 1");

    QVariant baseMaxCardNumber;
    if (SqlUtils::getInstance()->sqlValue(db.get(), command, baseMaxCardNumber))
    {
        SqlManager::getInstance().closeDB();
        return QString::number(baseMaxCardNumber.toLongLong() + 1);
    }
    SqlManager::getInstance().closeDB();

    return QString();
}

FullUserInfo::FullUserInfo() : UserInfo()
{
    login = "";
    password = "";
}

FullUserInfo::FullUserInfo(const QSqlRecord &record) : UserInfo(record)
{
    login = record.value("login").toString();
    password = record.value("password").toString();
}

void FullUserInfo::fillSqlData(QStringList &fields, QVariantList &values)
{
    fields << "login"; values << login;
    fields << "password"; values << password;
}

Genre::Genre()
{
    name = "";
}

Genre::Genre(const QSqlRecord &record)
{
    qDebug("Genre::Genre(const QSqlRecord &record)");
    id = record.value("id").toLongLong();

    name = record.value("name").toString();
}

void Genre::fillSqlData(QStringList &fields, QVariantList &values)
{
    fields << "name"; values << name;
}

Publishing::Publishing()
{
    name = "";
}

Publishing::Publishing(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    name = record.value("name").toString();
}

void Publishing::fillSqlData(QStringList &fields, QVariantList &values)
{
    fields << "name"; values << name;
}

Author::Author()
{

}

Author::Author(const QSqlRecord &record)
{
    id = record.value("id").toLongLong();

    firstName = record.value("first_name").toString();
    middleName = record.value("middle_name").toString();
    lastName = record.value("last_name").toString();

    setName();
}

void Author::fillSqlData(QStringList &fields, QVariantList &values)
{
    fields << "first_name"; values << firstName;
    fields << "middle_name"; values << middleName;
    fields << "last_name"; values << lastName;
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
    genre = record.value("genres").toString();
    publishing = record.value("publishing").toString();
    setDataList(record.value("authors").toString(), authors);
}

void Book::fillSqlData(QStringList &fields, QVariantList &values)
{
    Q_UNUSED(fields)
    Q_UNUSED(values)
//    fields << "name"; values << name;
//    fields << "all_count"; values << allCount;
//    fields << "current_count"; values << currentCount;
//    fields << "genres"; values << genres;
//    fields << "authors"; values << authors;
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
