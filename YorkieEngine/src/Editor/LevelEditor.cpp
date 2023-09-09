#include "Editor/LevelEditor.h"
#include "UI/imgui.h"
#include "UI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "UI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "Graphics/Renderer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

LevelEditor::LevelEditor(WindowProperties windowProps, Level * level) : bIsInGame(false), Window(windowProps)
{
    m_CurrentLevel = level;
    input = new Input(*this);
}

void LevelEditor::Init()
{
    SetLevelEditorFlags();

    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window,
        [](GLFWwindow* window, double xpos, double ypos) {

            LevelEditor* instance = static_cast<LevelEditor*>(glfwGetWindowUserPointer(window));
            if (instance) {
                instance->mouse_callback(window, xpos, ypos);
            }
        });

    InitUI();
    m_CurrentLevel->Init();
    Renderer::Init(*window);
}
void LevelEditor::Update(float deltaTime)
{
    Renderer::ClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Poll for events
    glfwPollEvents();

    EditorInput();
    ImGui::ShowDemoWindow();
    
    Renderer::DrawScene(*m_CurrentLevel);

    const int tabWidthAdjuster = 10;

    ImGuiStyle& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(12.0f, 8.0f);
    //style.ScaleAllSizes(24.f);
    ///////////////////////////////////////////////////////////////////
    /////////////////////// EDITOR TOP OPTIONS ////////////////////////
    //////////////////////////////////////////////////////////////////

    const ImVec2 editorTopOptionsWindowSize = ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y/30);
    //const ImVec2 editorTopOptionsWindowSizeConstraintMinimum = ImVec2(editorTopOptionsWindowSize.x / 2, editorTopOptionsWindowSize.y / 2);
    //const ImVec2 editorTopOptionsWindowSizeConstraintMaximum = ImVec2(editorTopOptionsWindowSize.x * 2, editorTopOptionsWindowSize.y * 2);
    const ImVec2 editorTopOptionsWindowPosition = ImVec2(0, 0);
    //ImGui::SetNextWindowSizeConstraints(editorTopOptionsWindowSizeConstraintMinimum, editorTopOptionsWindowSizeConstraintMaximum);
    ImGui::SetNextWindowSize(editorTopOptionsWindowSize);
    ImGui::SetNextWindowPos(editorTopOptionsWindowPosition, ImGuiCond_Once);

    if (ImGui::Begin("WindowTopBar", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowFontScale(1.5f);

        if (ImGui::BeginTabBar("File", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("File")) {

                ImGui::Text("File");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    ///////////////////////////////////////////////////////////////////
    ///////////////////////// OUTLINER ///////////////////////////////
    //////////////////////////////////////////////////////////////////

    const ImVec2 sceneHierarchyWindowSize = ImVec2(ImGui::GetIO().DisplaySize.x / tabWidthAdjuster, ImGui::GetIO().DisplaySize.y / 1.4);
    const ImVec2 sceneHierarchyWindowSizeConstraintMinimum = ImVec2(sceneHierarchyWindowSize.x/2, sceneHierarchyWindowSize.y/2);
    const ImVec2 sceneHierarchyWindowSizeConstraintMaximum = ImVec2(sceneHierarchyWindowSize.x * 2, sceneHierarchyWindowSize.y * 2);
    const ImVec2 sceneHierarchyWindowPosition = ImVec2(0, editorTopOptionsWindowSize.y);
    ImGui::SetNextWindowSizeConstraints(sceneHierarchyWindowSizeConstraintMinimum, sceneHierarchyWindowSizeConstraintMaximum);
    ImGui::SetNextWindowSize(sceneHierarchyWindowSize);
    ImGui::SetNextWindowPos(sceneHierarchyWindowPosition, ImGuiCond_Once);


    if (ImGui::Begin("Outliner", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowFontScale(1.5f);

        if (ImGui::BeginTabBar("LeftTabBar", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("Outliner")) {

                ImGui::Text("This is Tab 1 content.");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    ///////////////////////////////////////////////////////////////////
    ///////////////////////// DETAILS ////////////////////////////////
    //////////////////////////////////////////////////////////////////
    
    const ImVec2 detailsWindowSize = ImVec2(ImGui::GetIO().DisplaySize.x / tabWidthAdjuster, sceneHierarchyWindowSize.y);
    const ImVec2 detailsWindowSizeConstraintMinimum = ImVec2(detailsWindowSize.x / 2, detailsWindowSize.y / 2);
    const ImVec2 detailsWindowSizeConstraintMaximum = ImVec2(detailsWindowSize.x * 2, detailsWindowSize.y * 2);
    //X same as above and Y should be outliner Y + outliner Y size. 
    const ImVec2 detailsWindowPosition = ImVec2(ImGui::GetIO().DisplaySize.x - detailsWindowSize.x, editorTopOptionsWindowSize.y);
    ImGui::SetNextWindowSizeConstraints(detailsWindowSizeConstraintMinimum, detailsWindowSizeConstraintMaximum);
    ImGui::SetNextWindowSize(detailsWindowSize);
    ImGui::SetNextWindowPos(detailsWindowPosition, ImGuiCond_Once);


    if (ImGui::Begin("Details", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowFontScale(1.5f);

        if (ImGui::BeginTabBar("Details", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("Details")) {

                ImGui::Text("Details tab");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    //////////////////////////////////////////////////////////////////
    ///////////////////// CONTENT BROWSER ////////////////////////////
    //////////////////////////////////////////////////////////////////

    const ImVec2 contentBrowerWindowSize = ImVec2(ImGui::GetIO().DisplaySize.x , ImGui::GetIO().DisplaySize.y - sceneHierarchyWindowPosition.y - editorTopOptionsWindowPosition.y);
    const ImVec2 contentBrowerWindowSizeConstraintMinimum = ImVec2(contentBrowerWindowSize.x / 2, contentBrowerWindowSize.y / 2);
    const ImVec2 contentBrowerWindowSizeConstraintMaximum = ImVec2(contentBrowerWindowSize.x * 2, contentBrowerWindowSize.y * 2);
    //X same as above and Y should be outliner Y + outliner Y size. 
    const ImVec2 contentBrowserWindowPosition = ImVec2(0, editorTopOptionsWindowSize.y + sceneHierarchyWindowSize.y);

    ImGui::SetNextWindowSizeConstraints(contentBrowerWindowSizeConstraintMinimum, contentBrowerWindowSizeConstraintMaximum);
    ImGui::SetNextWindowSize(contentBrowerWindowSize);
    ImGui::SetNextWindowPos(contentBrowserWindowPosition, ImGuiCond_Once);

    if (ImGui::Begin("Content Browser", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetWindowFontScale(1.5f);

        if (ImGui::BeginTabBar("Content Browser", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("Content Browser")) {

                ImGui::Text("Content Browser tab");

                ImGui::EndTabItem();
            }

            // Tab 2
            if (ImGui::BeginTabItem("Console Log")) {

                ImGui::Text("Console Log");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    glfwSwapBuffers(window);
}

void LevelEditor::mouse_callback(GLFWwindow* window, double xposParam, double yposParam)
{
    if (bIsInGame)
    {
        float xpos = static_cast<float>(xposParam);
        float ypos = static_cast<float>(yposParam);

        float xoffset = xpos - m_mouseLastX;
        float yoffset = m_mouseLastY - ypos; // reversed since y-coordinates go from bottom to top
        m_mouseLastX = xpos;
        m_mouseLastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        m_CurrentLevel->GetGamera().AddRotation(0, yoffset, xoffset);

        m_CurrentLevel->GetGamera().SetCameraDirections();
    }
}

void LevelEditor::EditorInput()
{
    // Poll for events
    glfwPollEvents();

    float cameraSpeed = 0.25f; // adjust accordingly
    auto& renderCamera = m_CurrentLevel->GetGamera();

    if (input->IsKeyPressed(EKeyboardKeys::KEY_LEFT_SHIFT))
        cameraSpeed *= 4;
    if (input->IsKeyPressed(EKeyboardKeys::KEY_W))
        renderCamera.AddOffstet(renderCamera.cameraFront * cameraSpeed);
    if (input->IsKeyPressed(EKeyboardKeys::KEY_S))
        renderCamera.AddOffstet(-(renderCamera.cameraFront * cameraSpeed));
    if (input->IsKeyPressed(EKeyboardKeys::KEY_A))
        renderCamera.AddOffstet(-(renderCamera.cameraRight * cameraSpeed));
    if (input->IsKeyPressed(EKeyboardKeys::KEY_D))
        renderCamera.AddOffstet(renderCamera.cameraRight * cameraSpeed);

    if (input->IsKeyPressed(EKeyboardKeys::KEY_ESCAPE))
    {
        
        if (bIsEscapeAvailable)
        {
            if (bIsInGame)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                m_mouseLastX = GetWindowWidth() / 2;
                m_mouseLastY = GetWindowHeight() / 2;
                glfwSetCursorPos(window, m_mouseLastX, m_mouseLastY);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                m_mouseLastX = GetWindowWidth() / 2;
                m_mouseLastY = GetWindowHeight() / 2;
                glfwSetCursorPos(window, m_mouseLastX, m_mouseLastY);
            }
            bIsEscapeAvailable = false;
            bIsInGame = !bIsInGame;
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
    {
        bIsEscapeAvailable = true;
    }

    glm::mat4 camView = glm::lookAt(renderCamera.GetPosition(), renderCamera.GetPosition() + renderCamera.cameraFront, renderCamera.cameraUp);
    renderCamera.SetViewMatrix(camView);
    Renderer::SetProjectionMatrix(renderCamera, GetAspectRatio());
}

void LevelEditor::SetLevelEditorFlags()
{
    glEnable(GL_DEPTH_TEST);

}

void LevelEditor::InitUI()
{
    //////////////////////
    //INIT IMGUI
    /////////////////////

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGuiIO& io = ImGui::GetIO();
    (void) io;
}

