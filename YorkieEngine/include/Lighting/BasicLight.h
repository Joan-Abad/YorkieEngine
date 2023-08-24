#pragma once
#include "glm.hpp"
#include "Engine/YorkieEngine.h"
#include "Graphics/Primitives/Cube.h"

class YorkieAPI BasicLight : public Cube
{
public:
	BasicLight(const char* name);

	glm::vec3 lightColor;
};

