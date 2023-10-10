#pragma once
#include <string>
#include "Engine/YorkieEngine.h"
#include <deque>
#include "UI/ImGUI/imgui.h"

#define RESET_COLOR "\033[0m"
#define INFO_COLOR "\033[37m"    // Light grey
#define WARNING_COLOR "\033[33m" // Yellow
#define ERROR_COLOR "\033[31m"   // Red

struct MessageOutput
{
    std::string tag;
    ImVec4 color;
    std::string message;
};

class YorkieAPI Logger
{
public:
    static void LogInfo(const std::string& message);
    static void LogWarning(const std::string& message);
    static void LogError(const std::string& message);
    static std::deque<MessageOutput>& GetMessages() { return Messages; };
private:
    static size_t maxSize;
    static std::deque<MessageOutput> Messages;
    static void Log(const std::string& tag, const std::string& message, const ImVec4 color);
};

