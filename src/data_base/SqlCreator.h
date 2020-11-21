#ifndef SQLCREATOR_H
#define SQLCREATOR_H

#include <QSqlDatabase>
#include "MainIncludes.h"

class SqlCreator
{

private:
    SqlCreator();

public:
    static SqlCreator &getInstance();

    void create(std::shared_ptr<QSqlDatabase> db);

private:
    void createTable(std::shared_ptr<QSqlDatabase> db, const QString &tableName, const QString &table);
    void addColumn(std::shared_ptr<QSqlDatabase> db, const QString &tableName,
                   const QString &columnName, const QString &columnType);
};

#endif // SQLCREATOR_H
