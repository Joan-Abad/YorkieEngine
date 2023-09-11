#include "Editor/LevelEditor.h"
#include "UI/imgui_impl_opengl3.h"
#include "UI/imgui_impl_glfw.h"
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

    IO = ImGui::GetIO();
    IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  
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
    (void)io;

    ImVec2 DisplaySize = {(float)GetWindowWidth(), (float)GetWindowHeight()};
    
    
    m_ContentBrowserSize = { DisplaySize.x * m_ContentBrowserPortionOfTheScreenSize.x, DisplaySize.y * m_ContentBrowserPortionOfTheScreenSize.y };
    m_ContentBrowserPosition = { DisplaySize.x * m_ContentBrowerPortionOfTheScreenPosition.x, DisplaySize.y * m_ContentBrowerPortionOfTheScreenPosition.y };
    m_OutlinerSize = { DisplaySize.x * m_OutlinerPortionOfTheScreenSize.x, DisplaySize.y * m_OutlinerPortionOfTheScreenSize.y };
    m_OutlinerPosition = { 0, m_ContentBrowserPosition.y - m_OutlinerSize.y };
    m_DetailsSize = { DisplaySize.x * m_DetailsPortionOfTheScreenSize.x, DisplaySize.y * m_DetailsPortionOfTheScreenSize.y };
    m_DetailsPosition = { DisplaySize.x - m_DetailsSize.x, m_ContentBrowserPosition.y - m_OutlinerSize.y };
    m_LevelButtonsLayoutSize = { DisplaySize.x - m_OutlinerSize.x - m_DetailsSize.x, DisplaySize.y * m_LevelPortionOfTheScreenHeightSize };
    m_SceneTextureSize = { DisplaySize.x - m_OutlinerSize.x - m_DetailsSize.x, DisplaySize.y - m_ContentBrowserSize.y - m_LevelButtonsLayoutSize.y};
    //Set render Image texture 

    //1- Create an FBO for the Scene Viewport:
    glGenFramebuffers(1, &sceneFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFrameBuffer);

    //Generate a frame buffer that the is attached to a texture 2D
    glGenTextures(1, &sceneTextureBuffer);
    glBindTexture(GL_TEXTURE_2D, sceneTextureBuffer);



    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_SceneTextureSize.x, m_SceneTextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTextureBuffer, 0);

    // Check for framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle framebuffer initialization error
        Logger::LogError("Error");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer


}

float LevelEditor::GetLevelSceneAspectRation()
{
    return m_SceneTextureSize.x / m_SceneTextureSize.y;
}



void LevelEditor::Update(float deltaTime)
{
    NewLevelEditorFrame();
    EditorInput();
    RenderUI();
    Render3DScene();
    glfwSwapBuffers(window);
}

void LevelEditor::NewLevelEditorFrame()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
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

    Renderer::SetProjectionMatrix(renderCamera, GetLevelSceneAspectRation());
}

void LevelEditor::SetLevelEditorFlags()
{
    glEnable(GL_DEPTH_TEST);


}

void LevelEditor::RenderUI()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    Renderer::ClearColor({ 0.2f, 0.2f, 0.2f, 1.f });
    
    const int tabWidthAdjuster = 10;

    ImGuiStyle& style = ImGui::GetStyle();
    style.FramePadding = ImVec2(12.0f, 8.0f);
    //style.ScaleAllSizes(24.f);
    
    ImVec2 DisplaySize = ImGui::GetIO().DisplaySize;

    //////////////////////////////////////////////////////////////////
    ///////////////////// CONTENT BROWSER ////////////////////////////
    //////////////////////////////////////////////////////////////////
       
    m_ContentBrowserSize = { DisplaySize.x * m_ContentBrowserPortionOfTheScreenSize.x, DisplaySize.y * m_ContentBrowserPortionOfTheScreenSize.y };
    m_ContentBrowserPosition = { DisplaySize.x * m_ContentBrowerPortionOfTheScreenPosition.x, DisplaySize.y * m_ContentBrowerPortionOfTheScreenPosition.y };
    contentBrowserFlags = ImGuiWindowFlags_NoDecoration;

    ImGui::SetNextWindowSize(m_ContentBrowserSize);
    ImGui::SetNextWindowPos(m_ContentBrowserPosition);

    if (ImGui::Begin("Content Browser", NULL, contentBrowserFlags))
    {
        ImGui::SetWindowFontScale(windowFontScale);

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

    ///////////////////////////////////////////////////////////////////
    ///////////////////////// OUTLINER ////////////////////////////////
    //////////////////////////////////////////////////////////////////

    m_OutlinerSize = { DisplaySize.x * m_OutlinerPortionOfTheScreenSize.x, DisplaySize.y * m_OutlinerPortionOfTheScreenSize.y };
    m_OutlinerPosition = { 0, m_ContentBrowserPosition.y - m_OutlinerSize.y };

    ImGui::SetNextWindowSize(m_OutlinerSize);
    ImGui::SetNextWindowPos(m_OutlinerPosition);

    if (ImGui::Begin("Outliner", NULL, contentBrowserFlags))
    {
        ImGui::SetWindowFontScale(windowFontScale);

        if (ImGui::BeginTabBar("Outliner", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("Outliner")) {

                ImGui::Text("This is Tab Outliner content.");

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    ///////////////////////////////////////////////////////////////////
    ///////////////////////// DETAILS ////////////////////////////////
    //////////////////////////////////////////////////////////////////

    
    m_DetailsSize = { DisplaySize.x * m_DetailsPortionOfTheScreenSize.x, DisplaySize.y * m_DetailsPortionOfTheScreenSize.y };
    m_DetailsPosition = { DisplaySize.x - m_DetailsSize.x, m_ContentBrowserPosition.y - m_OutlinerSize.y };

    ImGui::SetNextWindowSize(m_DetailsSize);
    ImGui::SetNextWindowPos(m_DetailsPosition);

    if (ImGui::Begin("Details", NULL, contentBrowserFlags))
    {
        ImGui::SetWindowFontScale(windowFontScale);

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

    m_LevelButtonsLayoutSize = { DisplaySize.x - m_OutlinerSize.x - m_DetailsSize.x, DisplaySize.y * m_LevelPortionOfTheScreenHeightSize };
    m_LevelButtonsLayoutPositions = { m_OutlinerSize.x, 0 };

    ImGui::SetNextWindowSize(m_LevelButtonsLayoutSize);
    ImGui::SetNextWindowPos(m_LevelButtonsLayoutPositions);
    int* p_open; 

    if (ImGui::Begin("Level buttons bar", NULL, contentBrowserFlags))
    {
        
            ImGui::Text("THESE ARE THE LEVEL BUTTONS SECTION");

        ImGui::End();
    }
}

void LevelEditor::Render3DScene()
{
    ImGui::SetNextWindowPos({m_OutlinerSize.x, m_LevelButtonsLayoutSize.y});
    ImGui::SetNextWindowSize({ m_SceneTextureSize});
    if (ImGui::Begin("Render Scene", false, 
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize))
    {

        glBindFramebuffer(GL_FRAMEBUFFER, sceneFrameBuffer);
        Renderer::ClearColor({ 0.2, 0.2, 0.2, 0.1 });
        Renderer::DrawScene(*m_CurrentLevel);
        // Create an ImGui image with the scene texture as the source
        ImGui::Image((void*)(intptr_t)sceneTextureBuffer, { m_SceneTextureSize.x, m_SceneTextureSize .y}, ImVec2(0, 1), ImVec2(1, 0));
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ImGui::End();
    }

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

