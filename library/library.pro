QT -= gui
QT += network sql
TARGET = library
TEMPLATE = lib
DEFINES += LIBRARY_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += logger/spdlog


SOURCES += \
    databasemanager.cpp \
    databasemanagerclient.cpp \
    databasemanagerserver.cpp \
    event.cpp \
    eventclientdao.cpp \
    eventdao.cpp \
    eventmodel.cpp \
    eventserializer.cpp \
    eventserverdao.cpp \
    library.cpp \
    message.cpp \
    messageutils.cpp


HEADERS += \
    databasemanager.h \
    databasemanagerclient.h \
    databasemanagerserver.h \
    event.h \
    eventclientdao.h \
    eventdao.h \
    eventmodel.h \
    eventserializer.h \
    eventserverdao.h \
    library.h \
    library_global.h \
    message.h \
    messageutils.h
