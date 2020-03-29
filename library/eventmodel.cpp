#include "eventmodel.h"

EventModel::EventModel(DatabaseManager &db, QObject *parent) : QAbstractTableModel(parent),
    database(db), events(database.eventDao->events())
{

}

QModelIndex EventModel::addEvent(const Event &event)
{
    int rowIndex = rowCount();
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    std::shared_ptr<Event> newEvent(new Event(event));
    database.eventDao->addEvent(newEvent);
    events->push_back(move(newEvent));
    endInsertRows();
    return index(rowIndex, 0);
}

int EventModel::rowCount(const QModelIndex &/*parent*/) const
{
    return events->size();
}

int EventModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant EventModel::data(const QModelIndex &index, int role) const
{
    const Event& event = *events->at(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return event.getId();
        }
        if (index.column() == 1) {
            return event.getTimeStamp();
        }

        if (index.column() == 2) {
            return event.getPriority();
        }
        if (index.column() == 3) {
            return event.getText();
        }
    }
    return QVariant();
}

QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QString("id");
            case 1:
                return QString("timestamp");
            case 2:
                return QString("priority");
            case 3:
                return QString("text");
        }
    }
    return QVariant();
}
