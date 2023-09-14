#include "Window/Window.h"
#include "Logging/Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp> // Include this header for glm::value_ptr
#include "Graphics/Shaders/Shader.h"
#include "UI/ImGUI/imgui.h"
#include "UI/ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "UI/ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL

Window::Window(const WindowProperties windowProperties)
{
    window = glfwCreateWindow(windowProperties.m_Width, windowProperties.m_Height, windowProperties.m_Title, nullptr, nullptr);
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

void Window::Update(float deltaTime)
{
    while (bDrawWindow)
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

float Window::GetAspectRatio()
{
    return (float)GetWindowWidth() / (float)GetWindowHeight();
}
