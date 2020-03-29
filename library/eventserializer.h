#ifndef EVENTSERIALIZER_H
#define EVENTSERIALIZER_H

#include <QDataStream>
#include "message.h"
#include "event.h"

QDataStream & operator<<(QDataStream &out, std::shared_ptr<Event> &event);

QDataStream & operator<<(QDataStream &out,  std::unique_ptr<EventList> &events);

QDataStream &operator>>(QDataStream &in,  std::shared_ptr<Event> event);

#endif // EVENTSERIALIZER_H
