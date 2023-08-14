#include "../Public/Window.h"
#include "../../Logging/Public/Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp> // Include this header for glm::value_ptr
#include "../../Shaders/Shader.h"
#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "../../ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL

Window::Window(int width, int height, const char* title, WindowMode windowMode) //: width(width), height(height), title(title), windowMode(windowMode)
{
    // Create a GLFW window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        Logger::LogError("WINDOW COULD NOT BE CREATED");
        glfwTerminate();
    }

    bDrawWindow = true;
}

void Window::Init()
{
}

void Window::Draw()
{
    while (bDrawWindow && !glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }
}

int Window::GetWindowWidth()
{
    //TODO: Return a vector2 instead
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::GetWindowHeight()
{
    //TODO: Return a vector2 instead
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}
