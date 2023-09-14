#pragma once
#include "Window/Window.h"
#include "Game/GameEntity.h"
#include "Engine/YorkieEngine.h"
#include "Game/Level.h"
#include "Camera/Camera.h"
#include "UI/ImGUI/imgui.h"
#include "GLFW/glfw3.h"

#include <vector>

struct YorkieAPI windowsLayoutInfo
{

};

class YorkieAPI LevelEditor : public Window
{
	friend class WindowManager;
	friend class Level;

protected: 
	virtual void Init();

	virtual void Update(float deltaTime);

public: 
	inline Level* GetCurrentLevel() const { return m_CurrentLevel; };

private:
	LevelEditor(WindowProperties windowProps, Level* level);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void NewLevelEditorFrame();
	void EditorInput();
	void SetLevelEditorFlags();
	void RenderUI();
	void Render3DScene();
	void WriteLogToFile();
	//TODO: Maybe could be set in another class
	void InitUI();
	void windowCloseCallback(GLFWwindow* window);
	float GetLevelSceneAspectRation();

	unsigned int sceneFrameBuffer;
	unsigned int sceneTextureBuffer;
	unsigned int renederBufferObject;

	bool bIsInGame;
	bool bIsEscapeAvailable;

	float m_mouseLastX;
	float m_mouseLastY;

	Level* m_CurrentLevel;
	Input* input;

	/**ImGuiIO**/

	ImGuiIO IO;

	float windowFontScale = 1.5f;

	//////////////////////////////////////////////////////////////////
	///////////////////// LEVEL SCENE ///////////////////////////////
	////////////////(////////////////////////////////////////////////
		//The texture size of the current render scene texture

	ImVec2 m_SceneTextureSize;
	ImVec2 m_ScenePosition;
	// Create a depth buffer
	GLuint customDepthBuffer;

	//////////////////////////////////////////////////////////////////
	///////////////////// CONTENT BROWSER ////////////////////////////
	//////////////////////////////////////////////////////////////////

	//The size of the content browser is stored here
	ImVec2 m_ContentBrowserSize; 
	//The position of the content browser is stored here
	ImVec2 m_ContentBrowserPosition;

	//The flags of the content browers of imgui
	ImGuiWindowFlags contentBrowserFlags;
	//How much % of the screen is going to ocuppy 1 = 100%, 0 = 0% and where you want it to be
	const ImVec2 m_ContentBrowserPortionOfTheScreenSize = {1, 0.2f};
	const ImVec2 m_ContentBrowerPortionOfTheScreenPosition = { 0, 0.8f };

	//////////////////////////////////////////////////////////////////
	///////////////////// CONSOLE LOG ////////////////////////////
	//////////////////////////////////////////////////////////////////

	//Used to check for setting the scroll to the bottom when messages are getting printed. 
	size_t m_MessageNum = 0;
	
	//////////////////////////////////////////////////////////////////
	///////////////////////  OUTLINER  ///////////////////////////////
	//////////////////////////////////////////////////////////////////

	//The size of the content browser is stored here
	ImVec2 m_OutlinerSize;
	//The position of the content browser is stored here
	ImVec2 m_OutlinerPosition;
	ImGuiWindowFlags m_OutlinerFlags;
	GameEntity* entitySelected;
	//How much % of the screen is going to ocuppy 1 = 100%, 0 = 0% and where you want it to be
	const ImVec2 m_OutlinerPortionOfTheScreenSize = { 0.15, 0.8f };

	//////////////////////////////////////////////////////////////////
	///////////////////////  DETAILS  ////////////////////////////////
	//////////////////////////////////////////////////////////////////

	ImVec2 m_DetailsSize;
	ImVec2 m_DetailsPosition;
	ImGuiWindowFlags m_DetailsFlags;
	const ImVec2 m_DetailsPortionOfTheScreenSize = { 0.15, 0.8f };

	//////////////////////////////////////////////////////////////////
	/////////////////////  LEVEL BUTTONS /////////////////////////////
	//////////////////////////////////////////////////////////////////

	
	ImVec2 m_LevelButtonsLayoutSize;
	ImVec2 m_LevelButtonsLayoutPositions;
	ImGuiWindowFlags m_LevelButtonsLayoutFlags;
	float m_LevelPortionOfTheScreenHeightSize = 0.05;

};
