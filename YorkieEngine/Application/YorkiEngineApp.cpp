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

void YorkiEngineApp::CreateApplication()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    // Create a GLFW window
    window = glfwCreateWindow(yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight, yorkiEngineAppInfo.title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Set the current context to the GLFW window
    glfwMakeContextCurrent(window);

    // After creating the GLFW window and making the context current
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    // Set the viewport
    glViewport(0, 0, yorkiEngineAppInfo.screenWidth, yorkiEngineAppInfo.screenHeight);

    std::vector<float> vertices = {
        // Front face
        -0.5f, -0.5f,  0.5f,  // Bottom-left vertex
         0.5f, -0.5f,  0.5f,  // Bottom-right vertex
         0.5f,  0.5f,  0.5f,  // Top-right vertex
        -0.5f,  0.5f,  0.5f,  // Top-left vertex
        // Back face
        -0.5f, -0.5f, -0.5f,  // Bottom-left vertex
         0.5f, -0.5f, -0.5f,  // Bottom-right vertex
         0.5f,  0.5f, -0.5f,  // Top-right vertex
        -0.5f,  0.5f, -0.5f,  // Top-left vertex
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Back face
        7, 6, 5,
        5, 4, 7,
        // Left face
        4, 0, 3,
        3, 7, 4,
        // Bottom face
        4, 5, 1,
        1, 0, 4,
        // Top face
        3, 2, 6,
        6, 7, 3
    };
    Shader vertexShader(R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )", GL_VERTEX_SHADER);

    Shader fragmentShader(R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0);  // White color
        }
    )"
        , GL_FRAGMENT_SHADER);

    RenderObject renderObject(vertices, indices); 
    renderObject.AttachVertexShader(vertexShader);
    renderObject.AttachFragmentShader(fragmentShader);
    RenderingSystem::AddObjectToRender(renderObject);

}

void YorkiEngineApp::Update()
{
    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        RenderingSystem::RenderObjects(window);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void YorkiEngineApp::TerminateApplication()
{
    // Terminate GLFW and exit
    glfwTerminate();
}
