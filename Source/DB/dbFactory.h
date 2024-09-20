/*
 * Holds the builder for a new sqlite database
 */
#ifndef DBFACTORY_H
#define DBFACTORY_H

#include <QtSql/QSqlDatabase>

class dbFactory{
public:
    dbFactory(){};

    QSqlDatabase get_database(QString, QString);
};

#endif // DBFACTORY_H
