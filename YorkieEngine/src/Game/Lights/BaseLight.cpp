#include "Game/Lights/BaseLight.h"

BaseLight::BaseLight(glm::vec3 lightColor, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor) : GameEntity()
{
	m_lightColor = lightColor;
	m_ambientColor = ambientColor;
	m_diffuseColor = diffuseColor;
	m_specularColor = specularColor;
}
