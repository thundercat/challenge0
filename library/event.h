#ifndef EVENT_H
#define EVENT_H

#include <QtGlobal>
#include <QString>
#include "memory"
#include "library_global.h"

using EventPriority = int;

class LIBRARRY_EXPORT Event
{
public:
    int id;
    QString timeStamp;
    QString text;

    EventPriority eventPriority;
    Event();
    EventPriority getPriority() const;

    QString getTimeStamp() const;
    QString getText() const;
    EventPriority getEventPriority() const;
    int getId() const;
    void setId(int value);
    void setTimeStamp(const QString &value);
    void setText(const QString &value);
    void setEventPriority(const EventPriority &value);

    QString toString() const;

};

typedef std::vector<std::shared_ptr<Event>> EventList;
#endif // EVENT_H
