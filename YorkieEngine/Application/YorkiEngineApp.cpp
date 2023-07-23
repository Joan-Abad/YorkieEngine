#include "YorkiEngineApp.h"
#include "../Rendering/RenderingSystem.h"
#include "../Shaders/Shader.h"
#include "../Rendering/RenderObject.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "../Window/Public/WindowManager.h"
#include "../Logging/Public/Logger.h"

YorkiEngineApp::YorkiEngineApp()
{

}

void YorkiEngineApp::Run()
{
    CreateApplication();
    //Update();
}
#ifdef RENDER_OPENGL
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

#endif // RENDER_OPENGL

void YorkiEngineApp::CreateApplication()
{
    InitializeGLFW();
    WindowManager::CreateWindow(yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight, yorkiEngineAppInfo.title);
    InitializeGLAD();
    OnCreateApplicationCallback();
    Update();
}

void YorkiEngineApp::Update()
{
    WindowManager::DrawWindows();
    /*
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen to black
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        OnPreDraw();
        RenderingSystem::RenderObjects(window);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        OnPostDraw();
    }
    */
}

void YorkiEngineApp::TerminateApplication()
{
#ifdef RENDER_OPENGL
    // Terminate GLFW and exit
    glfwTerminate();
#endif
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
