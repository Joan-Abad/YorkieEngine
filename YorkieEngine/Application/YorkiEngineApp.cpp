#include "YorkiEngineApp.h"
#include "../Rendering/RenderingSystem.h"
#include "../Shaders/Shader.h"
#include "../Rendering/RenderObject.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "../Window/Public/WindowManager.h"
#include "../Logging/Public/Logger.h"
#include "../Window/Public/Viewport.h"
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_opengl3.h"
#include "../ImGUI/imgui_impl_glfw.h"

YorkiEngineApp::YorkiEngineApp()
{

}

void YorkiEngineApp::Run()
{
    CreateApplication();
    //Update();
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


void YorkiEngineApp::CreateApplication()
{
    InitializeGLFW();
    Window* window = WindowManager::CreateWindow<Viewport>(yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight, yorkiEngineAppInfo.title);
    InitializeGLAD();
    OnCreateApplicationCallback();
    Update();
}

void YorkiEngineApp::Update()
{
    WindowManager::DrawWindows();
}

void YorkiEngineApp::TerminateApplication()
{
    // Terminate GLFW and exit
    glfwTerminate();
}

void YorkiEngineApp::OnCreateApplicationCallback()
{
}

void YorkiEngineApp::OnPreDraw()
{
}

void YorkiEngineApp::OnPostDraw()
{
}

void YorkiEngineApp::OnTerimateApplication()
{
}
