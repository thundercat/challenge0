#ifndef SYSLOGQTHANDLER_H
#define SYSLOGQTHANDLER_H

#include <QDebug>
#include <QString>
#include <sys/syslog.h>

void syslogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // SYSLOGQTHANDLER_H
