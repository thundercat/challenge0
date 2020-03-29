#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include "message.h"
#include "eventdao.h"

class Socket : public QObject
{
    Q_OBJECT
public:
    Socket(QTcpSocket *socket, const EventDao&eventDao);

private:
    void onReadyRead();

    void handleClientRegister(std::shared_ptr<Message> message);
    void handleClientUnregister(std::shared_ptr<Message> message);
    void handleClientAddEvent(std::shared_ptr<Message> message);
    void handleClientGetEvents(std::shared_ptr<Message> message);
    void unregisterMe();
private:
    QTcpSocket *socket;
    QDataStream socketReader;
    const EventDao &eventDao;
signals:
    void unregister(Socket*);
};

#endif // SOCKET_H
