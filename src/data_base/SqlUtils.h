#ifndef SQLUTILS_H
#define SQLUTILS_H

#include <QObject>
#include <QPointer>
#include <QMutex>

class QSqlDatabase;
class QSqlRecord;
class QSqlQuery;

class SqlUtils : public QObject
{
    Q_OBJECT

    static SqlUtils *utils;
    static QMutex mutex;

protected:
    explicit SqlUtils(QObject *parent = nullptr);

public:
    static SqlUtils *instance();

    // replace all data by query
    // command example:
    //                 SELECT */any column name FROM base WHERE ...
    bool sqlTable(QSqlDatabase * db, const QString &command, QList<QSqlRecord> &records);
    bool sqlInsert(QSqlDatabase *db, const QString &table, const QStringList &fields, const QStringList &values);
    bool sqlUpdate(QSqlDatabase *db, const QString &table, const QStringList &fields, const QStringList &values, const QString &filter = "");
    bool sqlExec(QSqlDatabase *db, const QString &command);
    bool sqlValue(QSqlDatabase *db, const QString &command, QVariant &result);

    qlonglong getLastTableId(QSqlDatabase *db);

private:
    void finishQuery(QSqlQuery &query);
    bool execCommand(QSqlDatabase *db, const QString &command);

};

#endif // SQLUTILS_H
