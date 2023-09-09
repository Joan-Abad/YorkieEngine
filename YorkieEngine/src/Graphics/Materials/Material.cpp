#include "Graphics/Materials/Material.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Shaders/Shader.h"
#include "glad/glad.h"
#include "glm.hpp"
#include <vector>

Material::Material(Shader* shader, Texture* albedo, Texture* specular, float shininess) : m_Shader(shader), m_Albedo(albedo), m_Specular(specular), m_Shininess(shininess)
{
	Diffuse = glm::vec3(0.1f);
	
    isUsingSpecular = m_Specular == nullptr ? false : true;
	
}
