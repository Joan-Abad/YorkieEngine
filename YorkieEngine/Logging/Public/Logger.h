#pragma once
#include <string>
#include "../../YorkieEngine.h"

#define RESET_COLOR "\033[0m"
#define INFO_COLOR "\033[37m"    // Light grey
#define WARNING_COLOR "\033[33m" // Yellow
#define ERROR_COLOR "\033[31m"   // Red

class YorkieAPI Logger
{
public:
    static void LogInfo(const std::string& message);
    static void LogWarning(const std::string& message);
    static void LogError(const std::string& message);

private:

    static void Log(const std::string& tag, const std::string& message, const std::string& color);
};

