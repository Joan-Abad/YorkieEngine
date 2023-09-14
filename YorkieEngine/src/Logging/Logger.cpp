#include "Logging/Logger.h"
#include <iostream>
#include <ctime>

std::vector<MessageOutput> Logger::Messages;

void Logger::LogInfo(const std::string& message)
{
    Log("[INFO]", message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void Logger::LogWarning(const std::string& message)
{
    Log("[WARNING]", message, ImVec4(1.0, 1.0, 0.0, 1.0));
}

void Logger::LogError(const std::string& message)
{
    Log("[ERROR]", message, ImVec4(1.0, 0, 0, 1.0));
}

void Logger::Log(const std::string& tag, const std::string& message, const ImVec4 color)
{   
    //std::cout << color << tag << " ";
    //std::cout << message << RESET_COLOR << std::endl;

    MessageOutput messageOutput;
    messageOutput.color = color;
    messageOutput.tag = tag;
    messageOutput.message = message;

    Messages.push_back(messageOutput);
}