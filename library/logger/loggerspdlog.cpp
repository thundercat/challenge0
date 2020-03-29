//
// Created by kw234 on 27.11.19.
//

#include "loggerspdlog.h"

void LoggerSpdlog::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    std::string txt = msg.toStdString();
    switch (type) {
        case QtDebugMsg:
            spdlog::debug(txt);
            break;
        case QtInfoMsg:
            spdlog::info(txt);
            break;
        case QtWarningMsg:
            spdlog::warn(txt);
            break;
        case QtCriticalMsg:
            spdlog::critical(txt);
            break;
        case QtFatalMsg:
            spdlog::error(txt);
            abort();
    }
}

void LoggerSpdlog::makeLogger(const std::string &filename, int count, int size) {
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, size, count);

    spdlog::sinks_init_list sink_list = {rotating_sink, stdout_sink};

    auto logger = std::make_shared<spdlog::logger>("logger", sink_list.begin(), sink_list.end());
    logger->flush_on(spdlog::level::trace);
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}

LoggerSpdlog::LoggerSpdlog(const std::string &filename, int count, int size) {
    makeLogger(filename, count, size);
}
