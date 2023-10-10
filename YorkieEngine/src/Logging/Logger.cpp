#include "Logging/Logger.h"
#include <iostream>
#include <ctime>

std::deque<MessageOutput> Logger::Messages;
size_t Logger::maxSize = 150;

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

    if (Messages.size() > maxSize)
        Messages.pop_front();

    Messages.push_back(messageOutput);
    
}