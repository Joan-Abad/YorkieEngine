#include "Logging/Logger.h"
#include <iostream>
#include <ctime>

void Logger::LogInfo(const std::string& message)
{
    Log("[INFO]", message, INFO_COLOR);
}

void Logger::LogWarning(const std::string& message)
{
    Log("[WARNING]", message, WARNING_COLOR);
}

void Logger::LogError(const std::string& message)
{
    Log("[ERROR]", message, ERROR_COLOR);
}

void Logger::Log(const std::string& tag, const std::string& message, const std::string& color)
{   
    std::cout << color << tag << " ";
    std::cout << message << RESET_COLOR << std::endl;
}