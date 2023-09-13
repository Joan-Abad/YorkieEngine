#include "Editor/EditorWindow.h"
#include "UI/ImGUI/imgui.h"

EditorWindow::EditorWindow(ImVec2 windowSize, ImVec2 windowPosition, ImGuiWindowFlags_ windowFlags)
{
	this->m_windowSize = windowSize;
	this->m_windowPosition = windowPosition;
}