#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Engine/YorkiEngineApp.h"
#include "Graphics/Shaders/Shader.h"
#include "Game/GameEntity.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window/WindowManager.h"
#include "Logging/Logger.h"
#include "Window/Viewport.h"
#include "UI/ImGUI/imgui.h"
#include "UI/ImGUI/imgui_impl_opengl3.h"
#include "UI/ImGUI/imgui_impl_glfw.h"
#include "Editor/LevelEditor.h"
#include "Graphics/Renderer.h"

double YorkieEngineApp::deltaTime = 0;

YorkieEngineApp::YorkieEngineApp() : bIsRunning(true)
{
    InitializeEngineModules();
}

void YorkieEngineApp::Run()
{
    CreateApplication();
    InitializeWindows();
    InitGame();
    Update();
}

void YorkieEngineApp::Shutdown()
{
    bIsRunning = false; 
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
}

void YorkieEngineApp::CreateEngineViewport()
{
    //TODO: Check if there was a level created and saved. Saved system not created for now. 
    //Creating a default level for now
    Level* level = new Level("Default Level");
    auto& levelEditor = *WindowManager::CreateWindow<LevelEditor>(yorkiEngineAppConfig.levelEditorWindowProps, level);

}

void YorkieEngineApp::InitGame()
{
    OnCreateApplicationCallback();
}

void YorkieEngineApp::InitializeWindows()
{
    WindowManager::InitWindows();
}

void YorkieEngineApp::Update()
{
    while (bIsRunning)
    {
        OnUpdate(deltaTime);
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

void YorkieEngineApp::OnUpdate(float deltaTime)
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
