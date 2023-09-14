#include "Window/Viewport.h"
#include "UI/ImGUI/imgui.h"
#include "UI/ImGUI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "UI/ImGUI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "Maths/Vector3D.h"
#include "Logging/Logger.h"
#include "Graphics/Primitives/Cube.h"
#include "Game/GameEntity.h"
#include "Graphics/Renderer.h"
#include "Modules/ShaderModule.h"
#include "Camera/Camera.h"
#include "gtc/matrix_transform.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "UI/ImGUI/ImGuizmo/ImGuizmo.h"
#include "gtc/type_ptr.hpp"
/*
Viewport::Viewport(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode),
    lastX(0), lastY(0), WorldUp(glm::vec3(0, 1, 0)), grid(nullptr), renderCamera(nullptr)
{
    isInGame = true;
    input.SetWindow(*this);
}

void Viewport::Init()
{
    glEnable(GL_DEPTH_TEST);
    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        Viewport* instance = static_cast<Viewport*>(glfwGetWindowUserPointer(window));
        if (instance) {
            instance->mouse_callback(window, xpos, ypos);
        }
        });

    Renderer::Init(*window);

    InitMouse();

    // Main loop
    InitViewportCamera();

    InitGameEntites();

}

void Viewport::Update(float deltaTime)
{
    // Poll for events
    glfwPollEvents();

    Renderer::ClearColor({ 0.2f, 0.2f, 0.2f, 1.f });

    ProcessInput();
    UpdateGameEntities(deltaTime);

    //Renderer::DrawScene(*this);
    DrawViewportUI();

    // Swap the front and back buffers
    glfwSwapBuffers(window);
}

void Viewport::DrawGameEntities(float deltaTime)
{
    for (const auto &renderObject : gameEntitites)
    {
        Renderer::RenderEntity(*renderCamera, *renderObject);
    }
}

void Viewport::InitImGUI()
{

}

void Viewport::ProcessInput()
{
    float cameraSpeed = 0.25f; // adjust accordingly

    if (input.IsKeyPressed(EKeyboardKeys::KEY_LEFT_SHIFT))
        cameraSpeed *= 4;
    if (input.IsKeyPressed(EKeyboardKeys::KEY_W))
        renderCamera->AddOffstet(renderCamera->cameraFront * cameraSpeed);
    if (input.IsKeyPressed(EKeyboardKeys::KEY_S))
        renderCamera->AddOffstet(-(renderCamera->cameraFront * cameraSpeed));
    if (input.IsKeyPressed(EKeyboardKeys::KEY_A))
        renderCamera->AddOffstet(-(renderCamera->cameraRight * cameraSpeed));
    if (input.IsKeyPressed(EKeyboardKeys::KEY_D))
        renderCamera->AddOffstet(renderCamera->cameraRight * cameraSpeed);

    if (input.IsKeyPressed(EKeyboardKeys::KEY_ESCAPE))
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

    glm::mat4 camView = glm::lookAt(renderCamera->GetPosition(), renderCamera->GetPosition() + renderCamera->cameraFront, renderCamera->cameraUp);
    renderCamera->SetViewMatrix(camView);
    Renderer::SetProjectionMatrix(*renderCamera, GetAspectRatio());
}

void Viewport::InitViewportCamera()
{
    //GameCamera
    //renderCamera = CreateEntity<Camera>(this);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Viewport::InitMouse()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    lastX = GetWindowWidth() / 2;
    lastY = GetWindowHeight() / 2;
    glfwSetCursorPos(window, lastX, lastY);

}
//-1535 298
void Viewport::mouse_callback(GLFWwindow* glfWindow, double xposIn, double yposIn)
{    
    if (isInGame)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos; 

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        renderCamera->AddRotation(0, yoffset, xoffset);
        
        renderCamera->SetCameraDirections();
    }
}

void Viewport::InitGameEntites()
{
    for (const auto& renderObject : gameEntitites)
    {
        renderObject->Init();
    }
}

void Viewport::UpdateGameEntities(float deltaTime)
{
    for (const auto& renderObject : gameEntitites)
    {
        renderObject->Update(deltaTime);
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

    
    DrawImGUIDemoWindow();

    ImGui::Begin("Outliner", &isWindowOpen, ImGuiWindowFlags_None);
    ImGui::SetWindowFontScale(1.5f); // Larger font scale

    ImGui::Text("GameEntities:");
    
    static int item_current_idx = 0; // Here we store our selection data as an index.
    GameEntity* ro = nullptr;
    if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
    {
        for (int n = 0; n < gameEntitites.size(); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(gameEntitites[n]->entityName.c_str(), is_selected))
            {
                item_current_idx = n;
                ro = gameEntitites[n];
                ImGui::SetItemDefaultFocus();
                break;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
            {
                ro = gameEntitites[n];
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }
    if (ro)
    {
        ImGui::Text("Details:");

        ///////////////////////////////
        ///// LOCATION
        //////////////////////////////
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

        ///////////////////////////////
        ///// ROTATION
        //////////////////////////////

        ImGui::Text("Rotation:");
        ImGui::SameLine();
        // Convert the float to a string
        std::string xRotation = " X: " + std::to_string((int)ro->GetRotation().roll);
        std::string yGetRotation = " Y: " + std::to_string((int)ro->GetRotation().pitch);
        std::string zGetRotation = " Z: " + std::to_string((int)ro->GetRotation().yaw);

        ImGui::Text(xRotation.c_str());
        ImGui::SameLine();
        ImGui::Text(yGetRotation.c_str());
        ImGui::SameLine();
        ImGui::Text(zGetRotation.c_str());

        ///////////////////////////////
        ///// SCALE
        //////////////////////////////

        ImGui::Text("Scale:");
        ImGui::SameLine();
        // Convert the float to a string
        std::string xScale = " X: " + std::to_string((int)ro->GetScale().x);
        std::string yScale = " Y: " + std::to_string((int)ro->GetScale().y);
        std::string zScale = " Z: " + std::to_string((int)ro->GetScale().z);

        ImGui::Text(xScale.c_str());
        ImGui::SameLine();
        ImGui::Text(yScale.c_str());
        ImGui::SameLine();
        ImGui::Text(zScale.c_str());
        auto projMat = &Renderer::GetProjectionMat()[0][0];

        ImGuizmo::BeginFrame();
        ImGuizmo::Enable(true);
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, GetWindowWidth(), GetWindowHeight());
        
        ImGuizmo::Manipulate(
            glm::value_ptr(renderCamera->GetView()),
            glm::value_ptr(Renderer::GetProjectionMat()),
            ImGuizmo::OPERATION::TRANSLATE,
            ImGuizmo::MODE::WORLD,
            glm::value_ptr(ro->RootComponent->GetModelMat4())
        );
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

void Viewport::DrawImGUIDemoWindow()
{
    // Create and render the ImGui demo window
    ImGui::ShowDemoWindow();
}

void Viewport::DrawLevel(float deltaTime)
{

}
*/