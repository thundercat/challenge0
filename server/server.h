#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include "databasemanagerserver.h"
#include "socket.h"
#include "servermanager.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    ~Server();
    void configure();

    void registerSocket(Socket *socket);

    void unregisterSocket(Socket* socket);

private:
    QList<Socket*> list;

    ServerManager serverManager;

    // QTcpServer interface
protected:
    void incomingConnection();
    QDataStream mSocketReader;
    DatabaseManagerServer databaseManager;
};

#endif // SERVER_H
