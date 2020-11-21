#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>
#include "MainIncludes.h"

class SqlManager
{
    std::shared_ptr<QSqlDatabase> db;

private:
    SqlManager();

public:
    static SqlManager &getInstance();
    ~SqlManager();

    std::shared_ptr<QSqlDatabase> openDB();
    void closeDB();
};

#endif // SQLMANAGER_H
