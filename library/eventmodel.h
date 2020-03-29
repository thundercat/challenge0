#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include "library_global.h"
#include <memory>
#include "event.h"
#include <QAbstractTableModel>
#include "databasemanager.h"

class LIBRARRY_EXPORT EventModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EventModel(DatabaseManager &db, QObject *parent = nullptr);
    QModelIndex addEvent(const Event & event);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    DatabaseManager& database;
    std::unique_ptr<EventList> events;
};

#endif // EVENTMODEL_H
