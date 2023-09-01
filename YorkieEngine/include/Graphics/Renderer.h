#pragma once
#include <vector>
#include <memory>
#include "Engine/YorkieEngine.h"
#include <string>
#include "glm.hpp"
#include "entt/entt.hpp"
#include "Game/GameEntity.h"
#include "Camera/Camera.h"

class YorkieAPI Renderer
{
public:
	static void Init(GLFWwindow& window);
	static void ClearColor(glm::vec4 color);
	static void DrawEntity(Camera& renderCamera, GameEntity& gameEntity);
	static void DrawGrid(Camera& renderCamera, Grid& grid);
	static void SetProjectionMatrix(Camera& renderCamera, float aspectRatio);
private: 
	void SetLightColorOnShaders();
	static void InitIm_GUI(GLFWwindow& window);
	static glm::mat4 projectionMat;
};

