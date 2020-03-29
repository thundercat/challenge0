#include "eventserializer.h"

QDataStream &operator<<(QDataStream &out, std::shared_ptr<Event> &event)
{
    out << event->getId() << event->getTimeStamp() << event->getPriority() << event->getText();
    return out;
}

QDataStream &operator>>(QDataStream &in, std::shared_ptr<Event> event)
{
    in >> event->id;
    in >> event->timeStamp;
    in >> event->eventPriority;
    in >> event->text;
    return in;
}

QDataStream &operator<<(QDataStream &out, std::unique_ptr<EventList> &events)
{
    for (const auto & event : *events.get())
    {
        out << event->getId() << event->getTimeStamp() << event->getPriority() << event->getText();
    }
    return out;
}
