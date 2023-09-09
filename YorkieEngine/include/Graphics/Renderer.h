#pragma once
#include <vector>
#include <memory>
#include "Engine/YorkieEngine.h"
#include <string>
#include "glm.hpp"
#include "entt/entt.hpp"
#include "Camera/Camera.h"
#include "Window/Viewport.h"

#include "Game/Lights/DirectionalLight.h"
#include "Game/GameEntity.h"
#include "Game/Level.h"

class Grid;

class YorkieAPI Renderer
{
public:
	static void Init(GLFWwindow& window);
	static void ClearColor(glm::vec4 color);
	static void RenderEntity(Camera& renderCamera, GameEntity& gameEntity);
	static void DrawGrid(Camera& renderCamera);
	static void DrawScene(Level & level);
	static void SetProjectionMatrix(Camera& renderCamera, float aspectRatio);
	inline static glm::mat4 &GetProjectionMat() { return projectionMat; };
	static DirectionalLight* m_DirectionalLight;

private: 
	void SetLightColorOnShaders();
	static void InitIm_GUI(GLFWwindow& window);
	static glm::mat4 projectionMat;

	//TODO: REMOVE TO LEVEL
	static Grid* m_sceneGrid;
};

