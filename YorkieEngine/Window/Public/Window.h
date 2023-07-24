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

protected:
	Window(int width, int height, const char* title, WindowMode windowMode);

	bool bDrawWindow;
	GLFWwindow* window;

	virtual void Draw();

	

public:
	inline GLFWwindow* GetWindow() { return window; };
	int GetWindowWidth();
	int GetWindowHeight();
	
	
};

