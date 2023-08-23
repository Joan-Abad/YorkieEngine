#include "../Public/Viewport.h"
#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "../../ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "../../Math/Vector3D.h"
#include "../../Logging/Public/Logger.h"
#include "../../Rendering/Primitives/Cube.h"
#include "../../Rendering/RenderObject.h"
#include "../../Modules/ShaderModule.h"
#include "../../Camera/Camera.h"
#include "gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{
    bFirstMouse = true;
    isInGame = true;
}

void Viewport::Init()
{
    InitRenderObjects();

    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        Viewport* instance = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->mouse_callback(window, xpos, ypos);
        }
        });

    InitImGUI();

    // Main loop
    InitViewportCamera();
    InitMouse();
}

void Viewport::Draw()
{
    // Poll for events
    glfwPollEvents();

    //Renderer::ClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    PreDrawRenderObjects();

    ProcessInput();
    
    DrawRenderObjects();
    DrawViewportUI();

    // Swap the front and back buffers
    glfwSwapBuffers(window);
}

void Viewport::AddRenderObject(RenderObject& renderObject)
{
    renderObjects.push_back(&renderObject);
    renderObject.SetViewport(this);
}

void Viewport::DrawRenderObjects()
{
    for (const auto &renderObject : renderObjects)
    {
        //Set MVP matrix 
        Shader& shader = renderObject->GetShader();
        shader.Bind();
        shader.SetUniformMat4("model", renderObject->GetModel());
        shader.SetUniformMat4("view", renderCamera->GetView());
        shader.SetUniformMat4("projection", renderCamera->GetProjection());

        //Draw
        renderObject->Draw();
    }
}

void Viewport::InitImGUI()
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Viewport::ProcessInput()
{
    const float cameraSpeed = 0.25f; // adjust accordingly

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        renderCamera->AddOffstet(glm::vec3(cameraSpeed * renderCamera->cameraFront));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        renderCamera->AddOffstet(-cameraSpeed * renderCamera->cameraFront);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        renderCamera->AddOffstet(-glm::normalize(glm::cross(renderCamera->cameraFront, renderCamera->cameraUp)) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        renderCamera->AddOffstet(glm::normalize(glm::cross(renderCamera->cameraFront, renderCamera->cameraUp)) * cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        if (isEscapeAvailable)
        {
            if (isInGame)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                lastX = GetWindowWidth() / 2;
                lastY = GetWindowHeight() / 2;
                glfwSetCursorPos(window, lastX, lastY);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                lastX = GetWindowWidth() / 2;
                lastY = GetWindowHeight() / 2;
                glfwSetCursorPos(window, lastX, lastY);
            }
            isEscapeAvailable = false;
            isInGame = !isInGame;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
    {
        isEscapeAvailable = true;
    }

    glm::mat4 camView = glm::lookAt(renderCamera->position, renderCamera->position + renderCamera->cameraFront, renderCamera->cameraUp);
    renderCamera->SetViewMatrix(camView);
    renderCamera->SetProjectionMatrix(GetAspectRatio());
}

void Viewport::InitViewportCamera()
{
    //GameCamera
    renderCamera = new Camera("Main Camera");
}

void Viewport::InitMouse()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Viewport::mouse_callback(GLFWwindow* glfWindow, double xposIn, double yposIn)
{    
    if (isInGame)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (bFirstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            bFirstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        renderCamera->yaw += xoffset;
        renderCamera->pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (renderCamera->pitch > 89.0f)
            renderCamera->pitch = 89.0f;
        if (renderCamera->pitch < -89.0f)
            renderCamera->pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(renderCamera->yaw)) * cos(glm::radians(renderCamera->pitch));
        front.y = sin(glm::radians(renderCamera->pitch));
        front.z = sin(glm::radians(renderCamera->yaw)) * cos(glm::radians(renderCamera->pitch));
        renderCamera->cameraFront = glm::normalize(front);
    }
    
}

void Viewport::SetRenderObjectMatrices(RenderObject& renderObj)
{
    //View matrix and projection matrix
    renderCamera->SetProjectionMatrix(GetAspectRatio());
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

void Viewport::DrawViewportUI()
{
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool isWindowOpen = true;
    // Create a window

    ImGui::Begin("Outliner", &isWindowOpen, ImGuiWindowFlags_None);
    ImGui::SetWindowFontScale(1.5f); // Larger font scale

    ImGui::Text("RenderObjects:");
    
    static int item_current_idx = 0; // Here we store our selection data as an index.
    RenderObject* ro = nullptr;
    if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
    {
        for (int n = 0; n < renderObjects.size(); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(renderObjects[n]->objectName, is_selected))
            {
                item_current_idx = n;
                ro = renderObjects[n];
                ImGui::SetItemDefaultFocus();
                break;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
            {
                ro = renderObjects[n];
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }
    if (ro)
    {
        ImGui::Text("Details:");
        ImGui::Text("Location:");
        ImGui::SameLine();
        // Convert the float to a string
        std::string xLocation = " X: " + std::to_string((int)ro->GetPosition().x);
        std::string yLocation = " Y: " + std::to_string((int)ro->GetPosition().y);
        std::string zLocation = " Z: " + std::to_string((int)ro->GetPosition().z);


        ImGui::Text(xLocation.c_str());
        ImGui::SameLine();
        ImGui::Text(yLocation.c_str());
        ImGui::SameLine();
        ImGui::Text(zLocation.c_str());

    }
    else
        Logger::LogError("RO NULL");

    ImGui::SetWindowSize(ImVec2(GetWindowWidth()/5, GetWindowHeight()/2)); // Set window size
    // Set window position to (x, y)
    ImGui::SetWindowPos(ImVec2(0, 0));
    // Add UI elements here

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}