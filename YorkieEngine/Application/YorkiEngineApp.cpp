#include "YorkiEngineApp.h"
#include "../Rendering/RenderingSystem.h"
#include "../Shaders/Shader.h"
#include "../Rendering/RenderObject.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"

YorkiEngineApp::YorkiEngineApp()
{

}

void YorkiEngineApp::Run()
{
    CreateApplication();
    Update();
}

void YorkiEngineApp::CreateApplication()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // Specify OpenGL version (in this case, 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    window = glfwCreateWindow(yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight, yorkiEngineAppInfo.title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    // Set the viewport size and register the framebuffer_size_callback
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set the callback for window resizing
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    OnCreateApplication();
}

void YorkiEngineApp::Update()
{
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
}

void YorkiEngineApp::TerminateApplication()
{
    // Terminate GLFW and exit
    glfwTerminate();
}

void YorkiEngineApp::OnCreateApplication()
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
// Function called when the window is resized
void YorkiEngineApp::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}