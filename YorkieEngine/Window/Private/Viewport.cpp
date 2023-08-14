#include "../Public/Viewport.h"
#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "../../ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "../../Rendering/RenderObject.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../../Math/Vector3D.h"
#include "../../Logging/Public/Logger.h"
#include "../../Rendering/Primitives/Cube.h"
#include "../../Modules/ShaderModule.h"

Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{

}

void Viewport::Init()
{
    InitRenderObjects();
}

void Viewport::Draw()
{
    // Clear the screen
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PreDrawRenderObjects();

    DrawRenderObjects();

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    // Poll for events
    glfwPollEvents();

}

void Viewport::AddRenderObject(RenderObject& renderObject)
{
    renderObjects.push_back(&renderObject);
    renderObject.window = this;
}

void Viewport::DrawRenderObjects()
{
    for (const auto &renderObject : renderObjects)
    {
        renderObject->Draw();
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

void Viewport::InitRenderObjects()
{
    for (const auto& renderObject : renderObjects)
    {
        renderObject->Init();
    }
}

void Viewport::PreDrawRenderObjects()
{
    for (const auto& renderObject : renderObjects)
    {
        renderObject->PreDraw();
    }
}
