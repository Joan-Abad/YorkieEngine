#include "../Public/Window.h"
#include "../../Logging/Public/Logger.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp> // Include this header for glm::value_ptr
#include "../../Shaders/Shader.h"

Window::Window(int width, int height, const char* title, WindowMode windowMode)
{
#ifdef RENDER_OPENGL
    // Create a GLFW window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        Logger::LogError("WINDOW COULD NOT BE CREATED");
        glfwTerminate();
    }
#endif // RENDER_OPENGL
    bDrawWindow = true;
}

void Window::Draw()
{
#ifdef RENDER_OPENGL
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
#endif
}
