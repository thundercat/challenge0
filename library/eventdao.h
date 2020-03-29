#ifndef EVENTDAO_H
#define EVENTDAO_H

#include <QVector>
#include <memory>
#include "event.h"

class EventDao
{
public:
    EventDao() = default;
    virtual ~EventDao() = default;
    virtual void init() const = 0;
    virtual void addEvent(std::shared_ptr<Event> event) const = 0;
    virtual std::unique_ptr<EventList> events() const = 0;
};

#endif // EVENTDAO_H
