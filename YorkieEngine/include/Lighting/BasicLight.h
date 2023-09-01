#pragma once
#include "glm.hpp"
#include "Engine/YorkieEngine.h"
#include "Graphics/Primitives/Cube.h"

class YorkieAPI BasicLight : public Cube
{
public:
	BasicLight();

    glm::vec3 m_lightColor; 
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    
};

