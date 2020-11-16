#include "SqlManager.h"
#include "SqlDefine.h"

SqlManager::SqlManager()
{

}

SqlManager &SqlManager::getInstance()
{
    static SqlManager manager;
    return manager;
}

SqlManager::~SqlManager()
{
    if (db)
    {
        closeDB();
    }
}

std::shared_ptr<QSqlDatabase> SqlManager::openDB()
{
    if (db && db->isOpen())
    {
        qDebug("Database is open.");
        return nullptr;
    }

    if (!db)
    {
        db = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE", QString("%1_db").arg(base_name)));
        db->setDatabaseName(base_path);
    }

    if (!db->open())
    {
        qDebug("Database openning error.");
        closeDB();
    }

    return db;
}

void SqlManager::closeDB()
{
    if (!db || !db->isValid())
    {
        return;
    }

    QString connectName = db->connectionName();

    if (db->isOpen())
    {
        db->close();
    }

    db.reset();
    QSqlDatabase::removeDatabase(connectName);
}
