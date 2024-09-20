/*
 * Header file for the sqlite database manager class
 */
#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>

class dbManager
{
private:
    QSqlDatabase m_db;
    QString m_db_name;
    QString m_db_host;

public:
    dbManager(QString, QString);
};

#endif // DBMANAGER_H
