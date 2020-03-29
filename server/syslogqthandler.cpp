#include "syslogqthandler.h"


void syslogMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)

    QByteArray localMsg = msg.toLocal8Bit();
      switch (type) {
      case QtDebugMsg:
          fprintf(stderr, "Debug: %s\n", localMsg.constData());
          syslog(LOG_DEBUG, "logger (debug): %s", localMsg.constData());
          break;
      case QtInfoMsg:
          fprintf(stderr, "Info: %s\n", localMsg.constData());
          syslog(LOG_INFO, "logger (info): %s", localMsg.constData());
          break;
      case QtWarningMsg:
          fprintf(stderr, "Warning: %s\n", localMsg.constData());
          syslog(LOG_WARNING, "logger (warning): %s", localMsg.constData());
          break;
      case QtCriticalMsg:
          fprintf(stderr, "Critical: %s\n", localMsg.constData());
          syslog(LOG_CRIT, "logger (critical): %s", localMsg.constData());
          break;
      case QtFatalMsg:
          fprintf(stderr, "Fatal: %s\n", localMsg.constData());
          syslog(LOG_ALERT, "logger (alert): %s", localMsg.constData());
          abort();
      }
}
