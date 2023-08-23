#pragma once
#include "glm.hpp"
#include "../YorkieEngine.h"
#include "../Rendering/Primitives/Cube.h"

class YorkieAPI BasicLight : public Cube
{
public:
	BasicLight(const char* name);

	glm::vec3 lightColor;
};

