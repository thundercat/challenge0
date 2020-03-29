#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "socket.h"
class Server;

class ServerManager
{
public:
    ServerManager(const Server &server);

    const Server &server;
};

#endif // SERVERMANAGER_H
