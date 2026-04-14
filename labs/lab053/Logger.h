#ifndef LOGGER_H
#define LOGGER_H

#include <string>

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger {
private:
    static int logLevel;
    static std::string levelToString(LogLevel level);

public:
    static void setLogLevel(LogLevel level);
    static void debug(const std::string& message, const std::string& tag);
    static void info(const std::string& message, const std::string& tag);
    static void warning(const std::string& message, const std::string& tag);
    static void error(const std::string& message, const std::string& tag);
};

#endif // LOGGER_H