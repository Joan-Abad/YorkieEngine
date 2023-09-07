#pragma once
#include "Window/Window.h"
#include "Game/GameEntity.h"
#include "Engine/YorkieEngine.h"
#include <vector>
class LevelEditor : public Window
{
	friend class WindowManager;
public:

protected: 
	virtual void Init();

	virtual void Update(float deltaTime);

private:
	LevelEditor(int width, int height, const char* title, WindowMode windowMode);

	void StartFrame();
	void EndFrame();

	void CreateLevelEditor();

	void DrawLevelEditor();

	void DrawOutliner();

	

	std::vector<GameEntity*> gameEntities;
};
