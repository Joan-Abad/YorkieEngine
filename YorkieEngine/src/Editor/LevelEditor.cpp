#include "Editor/LevelEditor.h"
#include "UI/imgui.h"
#include "UI/imgui_impl_glfw.h" // Include the proper ImGui backend for GLFW
#include "UI/imgui_impl_opengl3.h" // Include the proper ImGui backend for OpenGL
#include "Graphics/Renderer.h"

LevelEditor::LevelEditor(int width, int height, const char* title, WindowMode windowMode) : Window(width, height, title, windowMode)
{

}

void LevelEditor::Init()
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void LevelEditor::Update(float deltaTime)
{
    DrawLevelEditor();
}

void LevelEditor::StartFrame()
{
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();
}

void LevelEditor::EndFrame()
{
    //ImGui::End();   
    //ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void LevelEditor::CreateLevelEditor()
{
    //StartFrame();
    DrawOutliner();
    //Create Details window
    //Create LevelScene
    //Create Content Browser
    //Create Place Actors window


}

void LevelEditor::DrawOutliner()
{

}

void LevelEditor::DrawLevelEditor()
{
    glfwPollEvents();
    Renderer::ClearColor(glm::vec4(0.0f));
    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("GameWindow");
    {
        // Using a Child allow to fill all the space of the window.
        // It also alows customization
        ImGui::BeginChild("GameRender");
        // Get the size of the child (i.e. the whole draw size of the windows).
        ImVec2 wsize = ImGui::GetWindowSize();
        // Because I use the texture from OpenGL, I need to invert the V from the UV.
        //ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }
    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Swap front and back buffers
    glfwSwapBuffers(window);
}

