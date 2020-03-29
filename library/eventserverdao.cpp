#include "eventserverdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QDebug>

EventServerDao::EventServerDao(QSqlDatabase &database) : database(database)
{

}

void EventServerDao::init() const
{
    if(!database.tables().contains("events"))
    {
        QSqlQuery query(database);
        query.exec("CREATE TABLE events(id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp TEXT, priority INT, text TEXT)");
    }
}

void EventServerDao::addEvent(std::shared_ptr<Event> event) const
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO events (timestamp, priority, text) VALUES (:timestamp, :priority, :text)");

    query.bindValue(":timestamp", event->getTimeStamp());
    query.bindValue(":priority", event->getPriority());
    query.bindValue(":text", event->getText());
    query.exec();
    event->setId(query.lastInsertId().toInt());
}

std::unique_ptr<EventList> EventServerDao::events() const
{
    QSqlQuery query("SELECT * FROM events", database);
    query.exec();
    std::unique_ptr<EventList> list = std::unique_ptr<EventList>(new EventList());

    while(query.next()) {
        std::unique_ptr<Event> event(new Event());
        event->setId(query.value("id").toInt());
        event->setTimeStamp(query.value("timestamp").toString());
        event->setEventPriority(query.value("priority").toInt());
        event->setText(query.value("text").toString());
        list->push_back(std::move(event));
    }
    return list;
}
