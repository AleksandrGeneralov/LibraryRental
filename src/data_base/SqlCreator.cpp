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
                    "user_id INTEGER,"
                    "type INTEGER(8),"
                    "name VARCHAR(255),"
                    "passport_series VARCHAR(255),"
                    "passport_number VARCHAR(255),"
                    "issued_organize VARCHAR(255),"
                    "registration VARCHAR(255),"
                    "card_number VARCHAR(255),"
                    "discount INTEGER(8)");

    createTable(db, "genres",
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name VARCHAR(255)");

    createTable(db, "publishing",
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name VARCHAR(255)");

    createTable(db, "authors",
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "first_name VARCHAR(255),"
                    "middle_name VARCHAR(255),"
                    "last_name VARCHAR(255)");

    createTable(db, "books",
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name VARCHAR(255),"
                    "all_count INTEGER(8),"
                    "current_count INTEGER(8),"
                    "genres_id INTEGER,"
                    "publishing_id INTEGER,"
                    "authors_id VARCHAR(255)");

    createTable(db, "books_history",
                    "book_id INTEGER,"
                    "client_id INTEGER,"
                    "issue_date VARCHAR(255),"
                    "return_date INTEGER");
}

void SqlCreator::createTable(std::shared_ptr<QSqlDatabase> db, const QString &tableName, const QString &table)
{
    SqlUtils::getInstance()->sqlExec(db.get(), QString("CREATE TABLE IF NOT EXISTS %1 (%2)").arg(tableName).arg(table));
}

void SqlCreator::addColumn(std::shared_ptr<QSqlDatabase> db, const QString &tableName, const QString &columnName, const QString &columnType)
{
    SqlUtils::getInstance()->sqlExec(db.get(), QString("ALTER TABLE %1 ADD COLUMN IF NOT EXISTS %2 %3").arg(tableName)
                                                                                                       .arg(columnName)
                                                                                                       .arg(columnType));
}
