#ifndef EVENTCLIENTDAO_H
#define EVENTCLIENTDAO_H

#include "eventdao.h"
#include <QTcpSocket>


class Obs {
public:
    virtual std::unique_ptr<EventList> events() = 0;
};

class Client;

class EventClientDao : public EventDao
{
public:
    EventClientDao(QTcpSocket &socket, Obs *client);

    // EventDao interface
public:
    void init() const override;

    void addEvent(std::shared_ptr<Event> event) const override;

    std::unique_ptr<EventList> events() const override;

private:
    QTcpSocket &socket;
    Obs *client;
};

#endif // EVENTCLIENTDAO_H
