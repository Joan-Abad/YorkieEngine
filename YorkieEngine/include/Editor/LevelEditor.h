#pragma once
#include "Window/Window.h"
#include "Game/GameEntity.h"
#include "Engine/YorkieEngine.h"
#include "Game/Level.h"
#include "Camera/Camera.h"

#include <vector>


class YorkieAPI LevelEditor : public Window
{
	friend class WindowManager;
	friend class Level;

protected: 
	virtual void Init();

	virtual void Update(float deltaTime);

private:
	LevelEditor(WindowProperties windowProps, Level* level);

	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void EditorInput();
	void SetLevelEditorFlags();

	//TODO: Maybe could be set in another class
	void InitUI();


	bool bIsInGame;
	bool bIsEscapeAvailable;

	float m_mouseLastX;
	float m_mouseLastY;

	Level* m_CurrentLevel;
	Input* input;
};
