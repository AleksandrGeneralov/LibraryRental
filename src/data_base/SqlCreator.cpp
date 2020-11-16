#include "SqlCreator.h"
#include "SqlUtils.h"

SqlCreator::SqlCreator()
{

}

SqlCreator &SqlCreator::getInstance()
{
    static SqlCreator creator;
    return creator;
}

void SqlCreator::create(std::shared_ptr<QSqlDatabase> db)
{
    createTable(db, "users",
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "login VARCHAR(255),"
                "password VARCHAR(255)");
    createTable(db, "users_info",
                "user_id INTEGER"
                "type INTEGER(8),"
                "name VARCHAR(255),"
                "passport_series VARCHAR(255),"
                "passport_number VARCHAR(255),"
                "issued_organize VARCHAR(255),"
                "registration VARCHAR(255),"
                "card_number VARCHAR(255),"
                "discount INTEGER(8)");
}

void SqlCreator::createTable(std::shared_ptr<QSqlDatabase> db, const QString &tableName, const QString &table)
{
    SqlUtils::getInstance()->sqlExec(db.get(), QString("CREATE TABLE IF NOT EXISTS %1 (%2)").arg(tableName).arg(table));
}
