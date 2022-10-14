#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <windows.h>

enum LogType
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry
{
    LogType type;
    std::string message;
};

class Logger
{
public:
    static void Log(const std::string& message);
    static void Err(const std::string& message);

private:
    static std::vector<LogEntry> messages;
    static std::string CurrentDateTimeToString();
};

#endif
