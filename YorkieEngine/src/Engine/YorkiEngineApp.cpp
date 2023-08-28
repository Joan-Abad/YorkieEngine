#include "Engine/YorkiEngineApp.h"
#include "Graphics/Shaders/Shader.h"
#include "Game/GameEntity.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window/WindowManager.h"
#include "Logging/Logger.h"
#include "Window/Viewport.h"
#include "UI/imgui.h"
#include "UI/imgui_impl_opengl3.h"
#include "UI/imgui_impl_glfw.h"

YorkiEngineApp::YorkiEngineApp() : bIsRunning(true)
{
    InitializeEngineModules();
}

void YorkiEngineApp::Run()
{
    CreateApplication();
    InitializeWindows();
    Update();
}
void YorkiEngineApp::InitializeGLFW()
{
    // Initialize GLFW
    if (!glfwInit())
        Logger::LogError("Failed to initialize GLFW");

    // Specify OpenGL version (in this case, 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1); // 1 means vsync is enabled

}

void YorkiEngineApp::InitializeGLAD()
{
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
}

void YorkiEngineApp::InitializeImGUI()
{
    
}

void YorkiEngineApp::InitializeEngineModules()
{
}

double YorkiEngineApp::GetTime()
{
    return glfwGetTime();
}

double YorkiEngineApp::SetDeltaTime()
{
    // Calculate frame time
    double currentTime = glfwGetTime();
    double frameTime = currentTime - previousTime;
    previousTime = currentTime;
    fpsTimeTracker += frameTime;

    FPS++;
    if (fpsTimeTracker > 1)
    {
        std::cout << "Frames per second: " << FPS << std::endl;
        FPS = 0; 
        fpsTimeTracker = 0; 
    }
    
    return frameTime;
}


void YorkiEngineApp::CreateApplication()
{
    InitializeGLFW();
    Window* window = WindowManager::CreateWindow<Viewport>(yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight, yorkiEngineAppInfo.title);
    InitializeGLAD();
    OnCreateApplicationCallback();
}

void YorkiEngineApp::InitializeWindows()
{
    WindowManager::InitWindows();
}

void YorkiEngineApp::Update()
{
    while (bIsRunning)
    {
        OnUpdate();
        OnPostUpdate();
        FPS++;
    }
}

void YorkiEngineApp::TerminateApplication()
{
    // Terminate GLFW and exit
    glfwTerminate();
}

void YorkiEngineApp::OnCreateApplicationCallback()
{
}

void YorkiEngineApp::OnUpdate()
{
    float deltaTime = SetDeltaTime();
    WindowManager::DrawWindows(deltaTime);
}

void YorkiEngineApp::OnPostUpdate()
{
}

void YorkiEngineApp::OnTerimateApplication()
{
}
