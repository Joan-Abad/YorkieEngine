#include "Game/Lights/PointLight.h"

PointLight::PointLight(glm::vec3 lightColor, float constant, float linear, float quadratic, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor) : 
	BaseLight(lightColor, ambientColor, diffuseColor, specularColor), m_constant(constant), m_linear(linear), m_quadratic(quadratic)
{

}
