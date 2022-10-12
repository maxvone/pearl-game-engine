#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <windows.h>

class Logger
{
public:
    static void Log(const std::string& message);
    static void Err(const std::string& message);

private:
    static std::string CurrentDateTimeToString();
};

#endif
