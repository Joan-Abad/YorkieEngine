#include "Editor/LevelEditor.h"
#include "UI/ImGUI/imgui_impl_opengl3.h"
#include "UI/ImGUI/imgui_impl_glfw.h"
#include "Graphics/Renderer.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
#include <fstream>
#include <filesystem>
#include <iostream>

LevelEditor::LevelEditor(WindowProperties windowProps, Level * level) : bIsInGame(false), Window(windowProps)
{
    m_CurrentLevel = level;
    input = new Input(*this);
    gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
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
    glfwSetWindowCloseCallback(window, 
        [](GLFWwindow* window) {
            LevelEditor* instance = static_cast<LevelEditor*>(glfwGetWindowUserPointer(window));
            if (instance)
            {
                instance->windowCloseCallback(window);
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
    //m_SceneTextureSize = { DisplaySize.x, DisplaySize.y};
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

    glGenRenderbuffers(1, &customDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, customDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_SceneTextureSize.x, m_SceneTextureSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, customDepthBuffer);

    // Check for framebuffer completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // Handle framebuffer initialization error
        Logger::LogError("Error setting the frame buffer for the scene rendering");
    }
    else
        Logger::LogInfo("Frame buffer for scene render set correctly");

    SetLevelEditorFlags();

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer

    fileTexture = new Texture("res/textures/Editor/Filee.png");

}

void LevelEditor::windowCloseCallback(GLFWwindow* window)
{
    bDrawWindow = false;
}

float LevelEditor::GetLevelSceneAspectRation()
{
    return m_SceneTextureSize.x / m_SceneTextureSize.y;
}



void LevelEditor::Update(float deltaTime)
{
    NewLevelEditorFrame();
    m_CurrentLevel->UpdateGameEntities(deltaTime);
    EditorInput();
    RenderUI();
    Render3DScene();
    //Renderer::ClearColor({ 0.2, 0.2, 0.2, 0.1 });
    //Renderer::DrawScene(*m_CurrentLevel);
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
        m_CurrentLevel->GetGamera().AddRotation(yoffset, xoffset, 0);
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
    if (input->IsKeyPressed(EKeyboardKeys::KEY_P))
        WriteLogToFile();
    

    if (entitySelected)
    {
        //Translate
        if (input->IsKeyPressed(EKeyboardKeys::KEY_E))
            gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        if (input->IsKeyPressed(EKeyboardKeys::KEY_R))
            gizmoOperation = ImGuizmo::OPERATION::ROTATE;
        if (input->IsKeyPressed(EKeyboardKeys::KEY_T))
            gizmoOperation = ImGuizmo::OPERATION::SCALE;
    }

    if (input->IsKeyPressed(EKeyboardKeys::KEY_ESCAPE))
    {
        
        if (bIsEscapeAvailable)
        {
            if (bIsInGame)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                m_mouseLastX = m_SceneTextureSize.x / 2;
                m_mouseLastY = m_SceneTextureSize.y / 2;
                glfwSetCursorPos(window, m_mouseLastX, m_mouseLastY);
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                m_mouseLastX = m_SceneTextureSize.x / 2;
                m_mouseLastY = m_SceneTextureSize.y / 2;
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

    /*
    if (bIsInGame)
    {
        std::string printMsg = "Camera Front: X: " + std::to_string(renderCamera.cameraFront.x)
            + " - Y: " + std::to_string(renderCamera.cameraFront.y)
            + " - Z: " + std::to_string(renderCamera.cameraFront.z) + 
            + " - Camera Up: X: " + std::to_string(renderCamera.cameraUp.x)
            + " - Y: " + std::to_string(renderCamera.cameraUp.y) +
            " - Z: " + std::to_string(renderCamera.cameraUp.z) + "\n";
        Logger::LogInfo(printMsg);
    }*/
}

void LevelEditor::SetLevelEditorFlags()
{
    glEnable(GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

    if (ImGui::Begin("BottomWindow", NULL, contentBrowserFlags))
    {
        ImGui::SetWindowFontScale(windowFontScale);

        if (ImGui::BeginTabBar("Content Browser", ImGuiTabBarFlags_Reorderable)) {

            // Tab 1
            if (ImGui::BeginTabItem("Content Browser")) {

                if (ImGui::BeginChild("Red", ImVec2(m_ContentBrowserSize.x - m_ContentBrowserSize.x * 0.005f, m_ContentBrowserSize.y - m_ContentBrowserSize.y * 0.15f), false, 0))
                {
                    static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV;

                    if (ImGui::BeginTable("table_padding", 8, flags1))
                    {

                        for (int row = 0; row < 15; row++)
                        {
                            if(row == 0)
                                ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 25));

                            ImGui::TableNextRow();
                            for (int column = 0; column < 8; column++)
                            {
                                ImGui::TableSetColumnIndex(column);                              


                                ImGui::ImageButton(
                                    "",
                                    (ImTextureID)fileTexture->GetTextureID(),     // Replace with your texture ID
                                    ImVec2(150, 150)
                                );
                                ImGui::Text("text");

                            }

                            if (row == 0)
                                ImGui::PopStyleVar();

                        }

                        ImGui::EndTable();
                    }

                    ImGui::EndChild();
                }
                ImGui::EndTabItem();
            }

            // Tab 2
            if (ImGui::BeginTabItem("Console Log")) {

                if (ImGui::BeginChild("Red", ImVec2(m_ContentBrowserSize.x - m_ContentBrowserSize.x * 0.005f, m_ContentBrowserSize.y - m_ContentBrowserSize.y * 0.18f), false, 0))
                {

                    for (const auto& message : Logger::GetMessages())
                    {
                        ImGui::TextColored(message.color, message.message.c_str());
                    }
                    if (Logger::GetMessages().size() > m_MessageNum)
                        ImGui::SetScrollHereY(1.0f);

                    m_MessageNum = Logger::GetMessages().size();

                    ImGui::EndChild();
                }
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

                ImGui::Text("Game Entities:");

                static int item_current_idx = 0; // Here we store our selection data as an index.
                if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
                {
                    const auto& GameEntitites = m_CurrentLevel->GetGameEntities();

                    for (int n = 0; n < m_CurrentLevel->GetGameEntities().size(); n++)
                    {
                        const bool is_selected = (item_current_idx == n);
                        if (ImGui::Selectable(GameEntitites[n]->entityName.c_str(), is_selected))
                        {
                            item_current_idx = n;
                            entitySelected = GameEntitites[n];
                            ImGui::SetItemDefaultFocus();
                            break;
                        }

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                        {
                            entitySelected = GameEntitites[n];
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndListBox();
                }

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
                
                if (entitySelected)
                {
                    ///////////////////////////////
                    ///// LOCATION
                    //////////////////////////////
                    ImGui::Text("Location:");

                    ImGui::Dummy(ImVec2(0, m_DetailsSize.y * 0.01f));

                    // Convert the float to a string
                    float loc[3] = { entitySelected->GetPosition().x , entitySelected->GetPosition().y, entitySelected->GetPosition().z };

                    bool modifiedX = false, modifiedY = false, modifiedZ = false;
                    
                    ImGui::Text("X: ");
                    ImGui::SameLine();
                    modifiedX = ImGui::DragFloat("##LocationX", &loc[0], 0.02f, -FLT_MAX, +FLT_MAX, " % .3f", 0);
                    

                    ImGui::Text("Y: ");
                    ImGui::SameLine();
                    modifiedY = ImGui::DragFloat("##LocationY", &loc[1], 0.02f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    ImGui::Text("Z: ");
                    ImGui::SameLine();
                    modifiedZ = ImGui::DragFloat("##LocationZ", &loc[2], 0.02f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    if (modifiedX || modifiedY || modifiedZ)
                        entitySelected->SetPosition(loc[0], loc[1], loc[2]);


                    ///////////////////////////////
                    ///// ROTATION
                    //////////////////////////////
                    
                    ImGui::Dummy(ImVec2(0, m_DetailsSize.y * 0.025f));

                    ImGui::Text("Rotation:");

                    ImGui::Dummy(ImVec2(0, m_DetailsSize.y * 0.01f));
                    
                    
                    modifiedX = false;
                    modifiedY = false;
                    modifiedZ = false;
                    const float constrot[3] = { entitySelected->GetRotation().pitch , entitySelected->GetRotation().yaw, entitySelected->GetRotation().roll };

                    // Convert the float to a string
                    float rot[3] = { entitySelected->GetRotation().pitch , entitySelected->GetRotation().yaw, entitySelected->GetRotation().roll };

                    ImGui::Text("P: ");
                    ImGui::SameLine();
                    modifiedX = ImGui::DragFloat("##RotationP", &rot[0], 0.58f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    ImGui::Text("Y: ");
                    ImGui::SameLine();
                    modifiedY = ImGui::DragFloat("##RotationY", &rot[1], 0.58f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    ImGui::Text("R: ");
                    ImGui::SameLine();
                    modifiedZ = ImGui::DragFloat("##RotationR", &rot[2], 0.58f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    if(modifiedX || modifiedY || modifiedZ)
                        entitySelected->SetRotation(rot[0], rot[1], rot[2]);

                    ///////////////////////////////
                    ///// SCALE
                    //////////////////////////////

                    modifiedX = false;
                    modifiedY = false;
                    modifiedZ = false;

                    ImGui::Dummy(ImVec2(0, m_DetailsSize.y * 0.025f));

                    ImGui::Text("Scale:");

                    ImGui::Dummy(ImVec2(0, m_DetailsSize.y * 0.01f));

                    // Convert the float to a string
                    float scale[3] = { entitySelected->GetScale().x , entitySelected->GetScale().y, entitySelected->GetScale().z };

                    ImGui::Text("X: ");
                    ImGui::SameLine();
                    modifiedX = ImGui::DragFloat("##ScaleX", &scale[0], 0.04f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    ImGui::Text("Y: ");
                    ImGui::SameLine();
                    modifiedY = ImGui::DragFloat("##ScaleY", &scale[1], 0.04f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    ImGui::Text("Z: ");
                    ImGui::SameLine();
                    modifiedZ = ImGui::DragFloat("##ScaleZ", &scale[2], 0.04f, -FLT_MAX, +FLT_MAX, " % .3f", 0);

                    if(modifiedX || modifiedY || modifiedZ)
                        entitySelected->SetScale(scale[0], scale[1], scale[2]);
                   
                }
                else
                    Logger::LogError("RO NULL");
                     
                entitySelected->ExtraDetailsWindow();

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

    if (ImGui::Begin("Level buttons bar", NULL, contentBrowserFlags))
    {
        
            ImGui::Text("THESE ARE THE LEVEL BUTTONS SECTION");

        ImGui::End();
    }

    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void PrintMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void LevelEditor::Render3DScene()
{
    m_ScenePosition = { m_OutlinerSize.x, m_LevelButtonsLayoutSize.y };
    
    ImGui::SetNextWindowPos(m_ScenePosition);
    ImGui::SetNextWindowSize({ m_SceneTextureSize});
    
    glBindFramebuffer(GL_FRAMEBUFFER, sceneFrameBuffer);
    glViewport(0, 0, m_SceneTextureSize.x, m_SceneTextureSize.y);
   
   

    if (ImGui::Begin("Render Scene", false, 
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking))
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        Renderer::ClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
        // Create an ImGui image with the scene texture as the source
        Renderer::DrawScene(*m_CurrentLevel);
       

        ImGui::Image((void*)(intptr_t)sceneTextureBuffer, ImVec2(m_SceneTextureSize.x, m_SceneTextureSize.y), ImVec2(0, 1), ImVec2(1, 0));

        if (entitySelected && entitySelected->GetCanDrawAxis())
        {
            //Draw ImGuizmo axis
            ImGuizmo::BeginFrame();
            ImGuizmo::Enable(true);
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            ImGuizmo::SetRect(m_ScenePosition.x, m_ScenePosition.y, m_SceneTextureSize.x, m_SceneTextureSize.y);
            
            glm::mat4& modelMat = entitySelected->RootComponent->modelMatrix;
            
                bool manipulated = ImGuizmo::Manipulate(
                    glm::value_ptr(m_CurrentLevel->m_renderCamera->GetView()),
                    glm::value_ptr(Renderer::GetProjectionMat()),
                    gizmoOperation,
                    ImGuizmo::MODE::WORLD,
                    glm::value_ptr(modelMat));

                if (manipulated)
                {
                    
                    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(modelMat), 
                        &entitySelected->RootComponent->position[0],
                        &entitySelected->RootComponent->rotation.pitch,
                        &entitySelected->RootComponent->scale[0]);

                }
        }
        ImGui::End();

    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //ImGui::SetWindowFontScale(1.0f);

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LevelEditor::WriteLogToFile()
{
    if (!std::filesystem::exists("Logs")) {
        // Create the directory
        if (std::filesystem::create_directory("Logs")) {
            Logger::LogInfo("Directory Logs created");
        }
        else {
            Logger::LogError("Directory Logs could not be created");
        }
    }
    else {
        Logger::LogInfo("Logs directory already exists.");
    }

    // Open a file for writing (creates the file if it doesn't exist)
    std::ofstream outputFile("Logs/LoggingFile2.txt");

    // Check if the file is open
    if (!outputFile.is_open()) {
        Logger::LogError("COULD NOT WRITE TO FILE LoggingFile.txt");
    }

    for (const auto& Message : Logger::GetMessages())
        outputFile << Message.message;

    // Close the file
    outputFile.close();

    Logger::LogInfo("Logging has been written to the Logs folder");
}

