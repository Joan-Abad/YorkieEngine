#pragma once
#include "Engine/YorkieEngine.h"
#include "Game/GameEntity.h"
#include "glm.hpp"

class YorkieAPI BaseLight : public GameEntity
{
public: 
	BaseLight(glm::vec3 lightColor = glm::vec3(1.0f), glm::vec3 ambientColor = glm::vec3(1.0f), glm::vec3 diffuseColor = glm::vec3(0.1f), glm::vec3 specularColor = glm::vec3(1.0f));

	/*inline glm::vec3 GetLightColor() { return m_lightColor; };
	inline glm::vec3 GetAmbientColor() { return m_ambientColor; };
	inline glm::vec3 GetDiffuseColor() { return m_diffuseColor; };
	inline glm::vec3 GetSpecularColor() { return m_specularColor; };
protected:*/ 
	glm::vec3 m_lightColor;
	glm::vec3 m_ambientColor;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;
};