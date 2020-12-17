#include "SqlUtils.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

SqlUtils *SqlUtils::utils = nullptr;
QMutex SqlUtils::mutex;

SqlUtils::SqlUtils(QObject *parent) : QObject(parent)
{

}

SqlUtils *SqlUtils::getInstance()
{
    QMutexLocker lock(&mutex);

    if (!utils)
    {
        utils = new SqlUtils();
    }

    return utils;
}

bool SqlUtils::sqlTable(QSqlDatabase *db, const QString &command, QList<QSqlRecord> &records)
{
    qDebug("SqlUtils::sqlTable");

    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    records.clear();
    QSqlQuery query(*db);
    if (!query.exec(command))
    {
        qDebug() << QString("Error execute query: %1").arg(query.lastQuery());
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().nativeErrorCode();
        finishQuery(query);
        return false;
    }
    else
    {
        records.reserve(query.size());
        while (query.next())
        {
            records.append(query.record());
        }
    }

    finishQuery(query);

    return true;
}

bool SqlUtils::sqlInsert(QSqlDatabase *db, const QString &table, const QStringList &fields, const QVariantList &values)
{
    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    if (fields.count() != values.count())
    {
        qDebug("Error sql insert: fields size != values size.");
        return false;
    }

    QStringList prepareFields;
    foreach (QString field, fields)
    {
        prepareFields.append(QString(":%1").arg(field));
    }

    QString command = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(table).arg(fields.join(",")).arg(prepareFields.join(","));

    QSqlQuery query(*db);
    query.prepare(command);

    for (int i = 0; i < prepareFields.count(); i++)
    {
        query.bindValue(prepareFields.at(i), values.at(i));
    }

    if (!query.exec())
    {
        qDebug() << QString("Error execute query: %1").arg(query.lastQuery());
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().nativeErrorCode();
        finishQuery(query);
        return false;
    }

    finishQuery(query);

    return true;
}

bool SqlUtils::sqlUpdate(QSqlDatabase *db, const QString &table, const QStringList &fields, const QStringList &values, const QString &filter)
{
    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    if (fields.count() != values.count())
    {
        qDebug("Error sql insert: fields size != values size.");
        return false;
    }

    QString filterCommand = filter.isEmpty() ? "1" : filter;
    QStringList preparedValues;

    for (int i = 0; i < fields.count(); i++)
    {
        preparedValues.append(QString("%1=%2").arg(fields.at(i)).arg(values.at(i)));
    }

    QString command = QString("UPDATE %1 SET %2 WHERE %3").arg(table).arg(preparedValues.join(",")).arg(filterCommand);

    return execCommand(db, command);
}

bool SqlUtils::sqlExec(QSqlDatabase *db, const QString &command)
{
    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    return execCommand(db, command);
}

bool SqlUtils::sqlValue(QSqlDatabase *db, const QString &command, QVariant &result)
{
    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    result.clear();
    QSqlQuery query(*db);
    if (!query.exec(command))
    {
        qDebug() << QString("Error execute query: %1").arg(query.lastQuery());
        finishQuery(query);
        return false;
    }
    else
    {
        if(!query.next())
        {
            qDebug("Error: list of values is empty");
        }
        else
        {
            result = query.value(0);
        }
    }

    finishQuery(query);

    return true;
}

bool SqlUtils::sqlIsExist(QSqlDatabase *db, const QString &table, const QStringList &fields, const QStringList &values)
{
    qDebug("SqlUtils::sqlIsExist");

    if (!db)
    {
        qDebug("Error sql insert: data base is not initialize.");
        return false;
    }

    if (fields.count() != values.count())
    {
        qDebug("Error sql insert: fields size != values size.");
        return false;
    }

    QStringList preparedValues;

    for (int i = 0; i < fields.count(); i++)
    {
        preparedValues.append(QString("%1='%2'").arg(fields.at(i)).arg(values.at(i)));
    }

    QList<QSqlRecord> records;
    if (sqlTable(db, QString("SELECT * FROM %1 WHERE %2").arg(table).arg(preparedValues.join(" AND ")), records))
    {
        if (!records.isEmpty())
        {
            return true;
        }
    }

    return false;
}

qlonglong SqlUtils::getLastTableId(QSqlDatabase *db, const QString &table)
{
    QVariant result = 0;
    sqlValue(db, QString("SELECT MAX(id) FROM %1").arg(table), result);

    return result.toLongLong();
}

void SqlUtils::finishQuery(QSqlQuery &query)
{
    query.clear();
    query.finish();
}

bool SqlUtils::execCommand(QSqlDatabase *db, const QString &command)
{
    QSqlQuery query(*db);
    if (!query.exec(command))
    {
        qDebug() << QString("Error execute query: %1").arg(query.lastQuery());
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().nativeErrorCode();
        finishQuery(query);
        return false;
    }

    finishQuery(query);

    return true;
}
