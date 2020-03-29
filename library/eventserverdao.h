#ifndef EVENTSERVERDAO_H
#define EVENTSERVERDAO_H

#include "eventdao.h"
#include "event.h"
#include "library_global.h"

class QSqlDatabase;

class EventServerDao : public EventDao
{
public:
    explicit EventServerDao(QSqlDatabase & database);
private:
    QSqlDatabase &database;

    // EventDao interface
public:
    void init() const override;
    void addEvent(std::shared_ptr<Event> event) const override;
    std::unique_ptr<EventList> events() const override;
};

#endif // EVENTSERVERDAO_H
