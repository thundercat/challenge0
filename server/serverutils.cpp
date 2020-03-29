#include "serverutils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <QString>
#include <QDateTime>

QString ServerUtils::getTimeStamp()
{
    QDateTime setTime = QDateTime::fromString (QString("1970-07-18T14:15:09"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    uint msecs = setTime.time().msecsTo(current.time());

    return  QString::number(msecs);
}

//http://www.netzmafia.de/skripten/unix/linux-daemon-howto.html
void ServerUtils::deamonize()
{
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
            exit(EXIT_FAILURE);
    }

    if (pid > 0) {
            exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
            exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
            exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
