#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window.h"
#include <vector>
#include "../../YorkieEngine.h"
#include "../../Camera/Camera.h"
class RenderObject;

class Yorkie Viewport : public Window
{
	friend class WindowManager;

protected:
	Viewport(int width, int height, const char* title, WindowMode windowMode);
	virtual void Init();
	virtual void Draw();

	Camera* renderCamera;
public:
	void AddRenderObject(RenderObject& renderObject);
	inline GLFWwindow* GetWindow() const { return window; };
private: 
	void InitRenderObjects();
	//PreDraw function for all render object before the current Render calls
	void PreDrawRenderObjects();
	void DrawRenderObjects(); 
	void DrawImGUiExample();
	void ProcessInput();
	std::vector<RenderObject*> renderObjects; 
	
};

