#include "server.h"
#include <QDebug>
#include "messageutils.h"
#include "eventserializer.h"

Server::Server(QObject *parent) : QTcpServer(parent), serverManager(*this)
{
    connect(this, &QTcpServer::newConnection, this, &Server::incomingConnection);
}

Server::~Server()
{
    for(auto& socket: list)
    {
        delete socket;
    }
}

void Server::configure()
{
    listen(QHostAddress::Any, 56556);
}

void Server::registerSocket(Socket *socket)
{
    connect(socket, &Socket::unregister, this, &Server::unregisterSocket);
    list.push_back(std::move(socket));
}

void Server::unregisterSocket(Socket *socket)
{
    qDebug() << "Server: unregister: socket";
    list.removeAll(socket);
}

void Server::incomingConnection()
{
    QTcpSocket * qSocket = nextPendingConnection();
    auto socket = new Socket(qSocket, *databaseManager.eventDao);

    qDebug() << "Incoming connection new client:" << qSocket->peerName() << qSocket->peerAddress().toString() << qSocket->peerPort();

    registerSocket(socket);
}

