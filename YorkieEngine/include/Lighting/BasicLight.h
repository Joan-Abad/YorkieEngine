#pragma once
#include "glm.hpp"
#include "Engine/YorkieEngine.h"
#include "Graphics/Primitives/Cube.h"

class YorkieAPI BasicLight : public Cube
{
public:
	BasicLight(Viewport* viewport);

	float ambientStrength;
	glm::vec3 lightColor;
};

