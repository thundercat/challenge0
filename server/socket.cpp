#include "socket.h"
#include "messageutils.h"
#include "event.h"
#include "eventserializer.h"
#include "serverutils.h"
#include <QDataStream>

Socket::Socket(QTcpSocket *socket, const EventDao &eventDao) : QObject(), socket(socket), eventDao(eventDao)
{
    socket->connect(socket, &QTcpSocket::readyRead, [this]{this->onReadyRead();});
    connect(socket, &QTcpSocket::disconnected, this, &Socket::unregisterMe);
    socketReader.setDevice(socket);
}

void Socket::onReadyRead()
{
    auto messages = MessageUtils::readMessages(socketReader);

//    qDebug() << "otrzymano dane, messages:" << messages->size();
    for(auto& message : *messages) {
        switch (message->type) {
        case Message::Type::CLIENT_REGISTER:
            handleClientRegister(message);
            qDebug() << "odebrano message cl register";
            break;
        case Message::Type::CLIENT_UNREGISTER:
            handleClientUnregister(message);
            qDebug() << "odebrano message cl unregister";

            break;
        case Message::Type::GET_EVENTS:
            handleClientGetEvents(message);
            qDebug() << "odebrano message get events";
            break;
        case Message::Type::UPDATED:
            // klient tego nie wysyla!!!!

            qDebug() << "odebrano message update";
            break;

        case Message::Type::ADD_EVENT:
//            qDebug() << "odebrano message add event";
            handleClientAddEvent(message);

        break;
        }
    }
}

void Socket::handleClientRegister(std::shared_ptr<Message> message)
{
    QByteArray data = message->data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    QString user, password;
    stream >> user >> password;
    qDebug() << "register user:" << user << "password:" << password;
}

void Socket::handleClientUnregister(std::shared_ptr<Message> /*message*/)
{
    emit unregister(this);
}

void Socket::handleClientAddEvent(std::shared_ptr<Message> message)
{
    // add event
    QByteArray data = message->data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    std::shared_ptr<Event> ev = std::shared_ptr<Event>(new Event());

    stream >> ev;
    qDebug() << "event" << ev->toString();

    ev->setTimeStamp(ServerUtils::getTimeStamp());
    eventDao.addEvent(ev);
}

void Socket::handleClientGetEvents(std::shared_ptr<Message> /*message*/)
{
    auto ret = eventDao.events();
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << ret;

    MessageUtils::sendMessage(*socket, Message::Type::UPDATED, data);
}

void Socket::unregisterMe()
{
    emit unregister(this);
}
