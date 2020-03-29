#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include "eventdao.h"
#include "library_global.h"


class LIBRARRY_EXPORT DatabaseManager
{
public:
    DatabaseManager() = default;
    virtual ~DatabaseManager() = default;

public:
    const EventDao *eventDao;
};

#endif // DATABASEMANAGER_H
