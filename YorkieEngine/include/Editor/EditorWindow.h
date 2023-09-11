#pragma once
#include "Engine/YorkieEngine.h"
#include "UI/imgui.h"

class YorkieAPI EditorWindow
{
public: 
	EditorWindow(ImVec2 windowSize, ImVec2 windowPosition, ImGuiWindowFlags_ windowFlags);

	void AddTabBar(const char* tabName);
	void AddTabItem();

	void Draw();

private:
	//The size of the editor window
	ImVec2 m_windowSize;

	//Which position will be the window on screen
	ImVec2 m_windowPosition;

	//Minimum size you can resize the window
	ImVec2 m_minimumConstraint;

	//Maximum size you can resize the window
	ImVec2 m_maximumConstraint;
};