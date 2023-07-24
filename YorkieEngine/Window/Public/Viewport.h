#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window.h"
#include <vector>

class RenderObject;

class Viewport : Window
{
	friend class WindowManager;

protected:
	Viewport(int width, int height, const char* title, WindowMode windowMode);

	virtual void Draw();

public:
	void AddRenderObject(RenderObject& renderObject);
	inline GLFWwindow* GetWindow() const { return window; };
private: 
	void DrawRenderObjects(); 
	void DrawImGUiExample();
	std::vector<RenderObject*> renderObjects; 
	
};

