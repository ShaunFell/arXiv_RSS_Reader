/*
 * source file for the sqlite database manager
 */

#include <QtSql/QSqlDatabase>

#include "dbManager.h"
#include "dbFactory.h"

dbManager::dbManager(QString host, QString name): m_db_name{name}, m_db_host{host}{
        dbFactory db_factory;
        m_db = db_factory.get_database(m_db_host, m_db_name);
    };
