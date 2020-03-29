//
// Created by kw234 on 27.11.19.
//

#ifndef APL432_LOGGERSPDLOG_H
#define APL432_LOGGERSPDLOG_H
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"
#include <QDebug>
#include "spdlog/spdlog.h"

class LoggerSpdlog {
public:
    explicit LoggerSpdlog(const std::string & filename, int count, int size);
    static void makeLogger(const std::string & filename, int count, int size);
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};


#endif //APL432_LOGGERSPDLOG_H
