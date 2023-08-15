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
#include "../../Camera/Camera.h"
#include "gtc/matrix_transform.hpp"

Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{

}

void Viewport::Init()
{
    InitRenderObjects();
    //GameCamera
    renderCamera = new Camera();
}

void Viewport::Draw()
{
    // Clear the screen
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PreDrawRenderObjects();

    ProcessInput();
    
    renderCamera->view = glm::lookAt(renderCamera->cameraPos, renderCamera->cameraPos + renderCamera->cameraFront, renderCamera->cameraUp);

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
        renderObject->Draw(renderCamera->view);
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

void Viewport::ProcessInput()
{
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderCamera->cameraPos += cameraSpeed * renderCamera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderCamera->cameraPos -= cameraSpeed * renderCamera->cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderCamera->cameraPos -= glm::normalize(glm::cross(renderCamera->cameraFront, renderCamera->cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderCamera->cameraPos += glm::normalize(glm::cross(renderCamera->cameraFront, renderCamera->cameraUp)) * cameraSpeed;
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
