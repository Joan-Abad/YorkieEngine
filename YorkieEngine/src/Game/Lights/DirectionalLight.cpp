#include "Game/Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 lightColor, glm::vec3 direction, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
	: BaseLight(lightColor, ambientColor, diffuseColor, specularColor)
{
	m_Direction = direction;
}

void DirectionalLight::SetLightDirection(glm::vec3& direction)
{
	m_Direction = direction;
}
