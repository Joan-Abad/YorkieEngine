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
#include "../../Rendering/Primitives/Cube.h"
Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{

}

void Viewport::Draw()
{
    Shader shader("res/shaders/default.shader");
    Cube cube;
    AddRenderObject(cube);

    while (bDrawWindow && !glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.ExecuteShader();
        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)GetWindowWidth() / (float)GetWindowHeight(), 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        GLint  modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
        GLint  viewLoc = glGetUniformLocation(shader.getProgramID(), "view");
        GLint  projLoc = glGetUniformLocation(shader.getProgramID(), "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //DrawImGUiExample();
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
