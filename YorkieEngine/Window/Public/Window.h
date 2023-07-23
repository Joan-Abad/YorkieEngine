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

private:
	Window(int width, int height, const char* title, WindowMode windowMode);

#ifdef RENDER_OPENGL
	GLFWwindow* window;
#endif

	bool bDrawWindow;

	virtual void Draw();

	

#ifdef RENDER_OPENGL
public:
	inline GLFWwindow* GetWindow() { return window; };
#endif
	
	
};

