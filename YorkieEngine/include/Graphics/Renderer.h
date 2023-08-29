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
	static void ClearColor(glm::vec4 color);
	static void DrawEntity(Camera& renderCamera, GameEntity& gameEntity);
private:
	//std::vector<int> VaoIn
};

