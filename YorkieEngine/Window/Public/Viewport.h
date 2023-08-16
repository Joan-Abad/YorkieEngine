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
	float lastX;
	float lastY;
	bool bFirstMouse;
	bool isInGame;	
	bool isEscapeAvailable;

public:
	void AddRenderObject(RenderObject& renderObject);
	void CharCallback(GLFWwindow* window, unsigned int c);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	inline GLFWwindow* GetWindow() const { return window; };
private: 
	void InitRenderObjects();
	//PreDraw function for all render object before the current Render calls
	void PreDrawRenderObjects();
	void DrawViewportUI();
	void DrawRenderObjects(); 
	void InitImGUI();
	void ProcessInput();
	void InitViewportCamera();
	void InitMouse();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	std::vector<RenderObject*> renderObjects; 
	
};

