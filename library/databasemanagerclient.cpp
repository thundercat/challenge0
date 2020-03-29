#include "databasemanagerclient.h"
#include "eventclientdao.h"

DatabaseManagerClient::DatabaseManagerClient(QTcpSocket &socket, Obs *obs)
{
    eventDao = new EventClientDao(socket, obs);
}
