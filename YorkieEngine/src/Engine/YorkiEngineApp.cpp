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

double YorkieEngineApp::deltaTime = 0;

YorkieEngineApp::YorkieEngineApp() : bIsRunning(true)
{
    InitializeEngineModules();
}

void YorkieEngineApp::Run()
{
    CreateApplication();
    InitializeWindows();
    Update();
}

void YorkieEngineApp::Shutdown()
{

}

void YorkieEngineApp::InitializeGLFW()
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

void YorkieEngineApp::InitializeGLAD()
{
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
}

void YorkieEngineApp::InitializeImGUI()
{
    
}

void YorkieEngineApp::InitializeEngineModules()
{
}

double YorkieEngineApp::GetGameTime()
{
    return glfwGetTime();
}

double YorkieEngineApp::GetDeltaTime()
{
    return deltaTime;
}

void YorkieEngineApp::SetDeltaTime()
{
    // Calculate frame time
    double currentTime = glfwGetTime();
    deltaTime = currentTime - previousTimeTracker;
    previousTimeTracker = currentTime;
    fpsTimeTracker += deltaTime;
    FPS++;

    if (fpsTimeTracker > 1)
    {
        //std::cout << "Frames per second: " << FPS << std::endl;
        FPS = 0; 
        fpsTimeTracker = 0; 
    }
}


void YorkieEngineApp::CreateApplication()
{
    InitializeGLFW();
    CreateEngineViewport();
    InitializeGLAD();
    OnCreateApplicationCallback();
}

void YorkieEngineApp::CreateEngineViewport()
{
    WindowManager::CreateWindow<Viewport>(yorkiEngineAppConfig.screenWidth, yorkiEngineAppConfig.screenHeight, yorkiEngineAppConfig.title);
}

void YorkieEngineApp::InitializeWindows()
{
    WindowManager::InitWindows();
}

void YorkieEngineApp::Update()
{
    while (bIsRunning)
    {
        OnUpdate();
        OnPostUpdate();
        FPS++;
    }
}

void YorkieEngineApp::TerminateApplication()
{
    // Terminate GLFW and exit
    glfwTerminate();
}

void YorkieEngineApp::OnCreateApplicationCallback()
{
}

void YorkieEngineApp::OnUpdate()
{
    SetDeltaTime();
    WindowManager::DrawWindows(deltaTime);
}

void YorkieEngineApp::OnPostUpdate()
{
}

void YorkieEngineApp::OnTerimateApplication()
{
}
