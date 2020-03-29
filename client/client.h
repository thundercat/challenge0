#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "eventclientdao.h"
#include "databasemanagerclient.h"
#include <QAbstractTableModel>
#include "message.h"

class Client : public QTcpSocket, public Obs
{
    QByteArray incomingData;
    Q_OBJECT
public:
    Client(QObject *parent=nullptr);

    void addEvent(std::shared_ptr<Event> event);
    void getEvents();

    void sendRegister();

    void sendMessage();

    QAbstractTableModel* getModel();

    void handleClientRegister(std::shared_ptr<Message> message);
    void handleClientUnregister(std::shared_ptr<Message> message);
    void handleClientAddEvent(std::shared_ptr<Message> message);
    void handleClientGetEvents(std::shared_ptr<Message> message);
    void handleClientUpdate(std::shared_ptr<Message> message);

private:
    DatabaseManager *databaseManager;
    QDataStream socketReader;

    void onReadyRead();

    // Obs interface
public:
    std::unique_ptr<EventList> events();

signals:
    void eventsReady();
};

#endif // CLIENT_H
