#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window.h"
#include <vector>
#include "../../YorkieEngine.h"
#include "entt/entt.hpp"

class RenderObject;
class Camera;

class YorkieAPI Viewport : public Window
{
	friend class WindowManager;

public:
	void AddRenderObject(RenderObject& renderObject);

	entt::registry registry;

	//GETTERS
	inline GLFWwindow* GetWindow() const { return window; };

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
	void SetRenderObjectMatrices(RenderObject& renderObj);
	std::vector<RenderObject*> renderObjects; 
};

