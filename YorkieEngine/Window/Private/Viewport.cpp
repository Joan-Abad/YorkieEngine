#include "../Public/Viewport.h"
#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "../../ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "../../Rendering/RenderObject.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../../Math/Vector3D.h"
#include "../../Logging/Public/Logger.h"

Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{

}

void Viewport::Draw()
{
   
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Initialize the GLFW backend for ImGui
    ImGui_ImplOpenGL3_Init("#version 330 core"); // Initialize the OpenGL backend for ImGui
    Shader shader("res/shaders/grid.shader");

    bool showWindowDemo = true;
    while (bDrawWindow && !glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawImGUiExample();

        DrawRenderObjects();

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();
    }
}

void Viewport::AddRenderObject(RenderObject& renderObject)
{
    renderObjects.push_back(&renderObject);
}

void Viewport::DrawRenderObjects()
{
    for (const auto &renderObject : renderObjects)
    {
        renderObject->Render();
    }
}

void Viewport::DrawImGUiExample()
{
    // Start a new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create ImGui widgets here
    ImGui::Text("Hello, ImGui!");

    // End the frame
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
