#ifndef DATABASEMANAGERSERVER_H
#define DATABASEMANAGERSERVER_H

#include "databasemanager.h"

class QSqlDatabase;

const QString DATABASE_FILENAME = "data.db";

class LIBRARRY_EXPORT DatabaseManagerServer : public DatabaseManager
{
public:
    DatabaseManagerServer(const QString& path = DATABASE_FILENAME);
    ~DatabaseManagerServer();

private:
    QSqlDatabase *database;
};

#endif // DATABASEMANAGERSERVER_H
