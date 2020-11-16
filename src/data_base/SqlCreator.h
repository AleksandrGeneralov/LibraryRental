#ifndef SQLCREATOR_H
#define SQLCREATOR_H

#include <QSqlDatabase>
#include <memory>

class SqlCreator
{

private:
    SqlCreator();

public:
    static SqlCreator &getInstance();

    void create(std::shared_ptr<QSqlDatabase> db);

private:
    void createTable(std::shared_ptr<QSqlDatabase> db, const QString &tableName, const QString &table);
};

#endif // SQLCREATOR_H
