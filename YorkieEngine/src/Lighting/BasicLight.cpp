#include "Lighting/BasicLight.h"
#include "Modules/ShaderModule.h"
BasicLight::BasicLight() : Cube(), 
m_lightColor(glm::vec3(1.0f)), m_ambient(glm::vec3(1.0f)), m_diffuse(glm::vec3(1.0f)), m_specular(glm::vec3(1.0f))
{
	//TODO delete this pointer
	Shader* shader = ShaderModule::GetShaderModule()->GetDefaultShader();
	AttachShader(shader);
	entityName = "BASIC LIGHT";

}
