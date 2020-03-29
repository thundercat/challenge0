#include "eventclientdao.h"
#include "event.h"
#include "eventserializer.h"
#include "message.h"
#include "messageutils.h"


EventClientDao::EventClientDao(QTcpSocket &socket, Obs *client) : socket(socket), client(client)
{

}

void EventClientDao::init() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream << QString("user") << QString("password");

    MessageUtils::sendMessage(socket,Message::Type::CLIENT_REGISTER,data, true);
}

void EventClientDao::addEvent(std::shared_ptr<Event> event) const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream << event;

    MessageUtils::sendMessage(socket, Message::Type::ADD_EVENT, data, true);
}

std::unique_ptr<EventList> EventClientDao::events() const
{
    return client->events();
}
