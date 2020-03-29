#include "databasemanagerserver.h"
#include <QSqlDatabase>

#include "eventserverdao.h"

DatabaseManagerServer::DatabaseManagerServer(const QString &path) :
    database(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    eventDao = new EventServerDao(*database);

    database->setDatabaseName(path);
    database->open();
    eventDao->init();
}

DatabaseManagerServer::~DatabaseManagerServer()
{
    database->close();
    delete database;
}
