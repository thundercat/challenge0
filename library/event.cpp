#include "event.h"

QString Event::getTimeStamp() const
{
    return timeStamp;
}

QString Event::getText() const
{
    return text;
}

EventPriority Event::getEventPriority() const
{
    return eventPriority;
}


int Event::getId() const
{
    return id;
}

void Event::setId(int value)
{
    id = value;
}

void Event::setTimeStamp(const QString &value)
{
    timeStamp = value;
}

void Event::setText(const QString &value)
{
    text = value;
}

void Event::setEventPriority(const EventPriority &value)
{
    eventPriority = value;
}

QString Event::toString() const
{
    return QString::number(id) + " " + timeStamp + " " + QString::number(eventPriority) + " " + text;
}

Event::Event() : id(-1), timeStamp(""), text(""), eventPriority(0)
{

}

EventPriority Event::getPriority() const
{
    return eventPriority;
}
