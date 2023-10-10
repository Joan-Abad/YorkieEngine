#pragma once
#include "Engine/YorkieEngine.h"
#include "BaseLight.h"
#include "glm.hpp"

class YorkieAPI DirectionalLight  : public BaseLight
{
public: 
	DirectionalLight(glm::vec3 lightColor = glm::vec3(1.0f), glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3 ambientColor = glm::vec3(0.01f), glm::vec3 diffuseColor = glm::vec3(1.0f), glm::vec3 specularColor = glm::vec3(1.0f));

	void SetLightDirection(glm::vec3& direction);
	inline const glm::vec3& GetLightDirection() { return m_Direction; };
private: 
	glm::vec3 m_Direction;

};