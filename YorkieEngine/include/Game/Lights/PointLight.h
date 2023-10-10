#include "BaseLight.h"
#include "Engine/YorkieEngine.h"

class YorkieAPI PointLight : public BaseLight
{
public: 
	PointLight(glm::vec3 lightColor = glm::vec3(1.0f), float constant = 1.f, float linear = 0.09f, float quadratic = 0.032f, 
		glm::vec3 ambientColor = glm::vec3(0.05f), glm::vec3 diffuseColor = glm::vec3(1.0f), glm::vec3 specularColor = glm::vec3(1.0f));

	float m_constant; 
	float m_linear;
	float m_quadratic;
};