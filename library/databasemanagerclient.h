#ifndef DATABASEMANAGERCLIENT_H
#define DATABASEMANAGERCLIENT_H

#include "databasemanager.h"
#include <QTcpSocket>
#include <eventclientdao.h>

class DatabaseManagerClient : public DatabaseManager
{
public:
    DatabaseManagerClient(QTcpSocket &socket, Obs *obs);
};

#endif // DATABASEMANAGERCLIENT_H
