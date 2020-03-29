#include "client.h"
#include "databasemanagerclient.h"
#include "eventmodel.h"
#include "messageutils.h"
#include "eventserializer.h"

Client::Client(QObject *parent) : QTcpSocket(parent)
{
    databaseManager = new DatabaseManagerClient(*this, this);
    connect(this, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(this, &QTcpSocket::connected, this, &Client::sendRegister);
    socketReader.setDevice(this);
}

void Client::addEvent(std::shared_ptr<Event> event)
{
    databaseManager->eventDao->addEvent(event);
}

void Client::getEvents()
{
    QByteArray data;
    MessageUtils::sendMessage(*this,Message::Type::GET_EVENTS,data, true);
}

void Client::sendRegister()
{
    databaseManager->eventDao->init();
    getEvents();
}

QAbstractTableModel *Client::getModel()
{
    return new EventModel(*databaseManager);
}

void Client::handleClientRegister(std::shared_ptr<Message> /*message*/){}
void Client::handleClientUnregister(std::shared_ptr<Message> /*message*/){}
void Client::handleClientAddEvent(std::shared_ptr<Message> /*message*/){}
void Client::handleClientGetEvents(std::shared_ptr<Message> /*message*/){}

void Client::handleClientUpdate(std::shared_ptr<Message> message)
{
    incomingData = message->data;
    emit eventsReady();
}

void Client::onReadyRead()
{
    auto messages = MessageUtils::readMessages(socketReader);

    for(auto& message : *messages) {
        switch (message->type) {
        case Message::Type::CLIENT_REGISTER:
            handleClientRegister(message);
            break;
        case Message::Type::CLIENT_UNREGISTER:
            handleClientUnregister(message);
            break;
        case Message::Type::GET_EVENTS:
            handleClientGetEvents(message);
            break;
        case Message::Type::UPDATED:
            handleClientUpdate(message);
            break;
        case Message::Type::ADD_EVENT:
            handleClientAddEvent(message);
        break;
        }
    }
}

std::unique_ptr<EventList> Client::events()
{
    QDataStream stream(&incomingData, QIODevice::ReadWrite);
    std::unique_ptr<std::vector<std::shared_ptr<Event>>> events = std::unique_ptr<EventList>(new EventList());

    while (!stream.atEnd())
    {
        std::shared_ptr<Event> ev = std::shared_ptr<Event>(new Event());
        stream >> ev;
        events->push_back(std::move(ev));
    }

    return events;
}
