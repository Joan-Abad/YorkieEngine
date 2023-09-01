#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Window.h"
#include <vector>
#include "Engine/YorkieEngine.h"
#include "entt/entt.hpp"
#include "glm.hpp"
#include "Input/Input.h"
#include "Editor/Grid.h"
#include "Logging/Logger.h"

class GameEntity;
class Camera;
class Shader;

class YorkieAPI Viewport : public Window
{
	friend class WindowManager;

public:
	//Function to call each time we want to create a game entity
	template<typename T = GameEntity, typename... Args>
	T* CreateEntity(Args&&... args)
	{
		T* gameEntity = new T(std::forward<Args>(args)...);
		if (gameEntity)
		{
			gameEntity->SetupEntity(this);
			gameEntitites.push_back(gameEntity);
		}
		else
			Logger::LogError("Game Entity could not be created");

		return gameEntity;
	}

	entt::registry registry;

	//GETTERS
	inline GLFWwindow* GetWindow() const { return window; };

protected:
	Viewport(int width, int height, const char* title, WindowMode windowMode);
	virtual void Init() override;
	virtual void Update(float deltaTime) override;

	//Check mouse last frame positions
	float lastX;
	float lastY;

	//Checks if it is navigating through the game editor
	bool isInGame;	
	bool isEscapeAvailable;
	//Stores the up vector of the world
	glm::vec3 WorldUp;
	Grid* grid;
	Camera* renderCamera;

private: 
	void InitGameEntites();
	//PreDraw function for all render object before the current Render calls
	void UpdateEntitiesComponents();
	void UpdateGameEntities(float deltaTime);
	void DrawViewportUI();
	void DrawImGUIDemoWindow();
	void DrawLevel(float deltaTime);
	void DrawGameEntities(float deltaTime);
	void InitImGUI();
	void ProcessInput();
	void Internal_CreateEntity();
	void InitViewportCamera();
	void InitMouse();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	std::vector<GameEntity*> gameEntitites; 
	Input input;
};

