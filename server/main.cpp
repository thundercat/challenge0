#include <QArgument>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "server.h"
#include "serverutils.h"
#include "syslogqthandler.h"

#include <sys/file.h>
#include <errno.h>

bool trySetPidLock()
{
    int pid_file = open("./server.pid", O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);
    if(rc) {
        if(EWOULDBLOCK == errno)
        {
            return false;
        }
    }
    else {
        return true;
    }
    return false;
}

void parseCommandLine(const QCoreApplication& app) {
  QCommandLineParser parser;
  parser.setApplicationDescription("Test helper");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption showProgressOption("d", QCoreApplication::translate("main", "Deamonize process"));
  parser.addOption(showProgressOption);
  parser.process(app);

  bool daemonize = parser.isSet(showProgressOption);

  if(daemonize)
  {
      if(trySetPidLock())
      {
          qDebug() << "Deamonize";
          ServerUtils::deamonize();
      }
      else
      {
          qDebug() << "proces uruchomionoy";
          exit(EXIT_FAILURE);
      }
  }
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);


  // syslog
  //    qInstallMessageHandler(syslogMessageHandler);

  qDebug() << "Application start";
  parseCommandLine(a);

  auto server = std::make_unique<Server>();
  server->configure();

  return a.exec();
}
