#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window.h"
#include <vector>
#include "Engine/YorkieEngine.h"
#include "entt/entt.hpp"

class GameEntity;
class Camera;
class Vertex;
class Shader;

class YorkieAPI Viewport : public Window
{
	friend class WindowManager;

public:
	GameEntity* CreateEntity(const char* objectName, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	GameEntity* CreateEntity(const char* objectName, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Shader& shader);

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
	void InitGameEntitys();
	//PreDraw function for all render object before the current Render calls
	void PreDrawGameEntitys();
	void DrawViewportUI();
	void DrawGameEntitys(); 
	void InitImGUI();
	void ProcessInput();
	void InitViewportCamera();
	void InitMouse();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void SetGameEntityMatrices(GameEntity& renderObj);
	std::vector<GameEntity*> renderObjects; 
};

