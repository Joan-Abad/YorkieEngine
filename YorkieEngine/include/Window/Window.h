#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"

enum class WindowMode
{
	Windowed,
	FullScreen,
	Borderless
};

class Window
{
	friend class WindowManager;
	friend class GameEntity;
public:
	Window() = default;
	Window(int width, int height, const char* title, WindowMode windowMode);
protected:
	bool bDrawWindow;
	GLFWwindow* window;

	virtual void Init();
	virtual void Draw();

public:
	inline GLFWwindow* GetWindow() { return window; };
	int GetWindowWidth();
	int GetWindowHeight();
	float GetAspectRatio();
	
};

