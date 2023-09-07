#pragma once
#include "Engine/YorkieEngine.h"
#include "Game/GameEntity.h"
#include "glm.hpp"

class YorkieAPI BaseLight : public GameEntity
{
public: 
	BaseLight(glm::vec3 lightColor = glm::vec3(1.0f), glm::vec3 ambientColor = glm::vec3(1.0f), glm::vec3 diffuseColor = glm::vec3(0.1f), glm::vec3 specularColor = glm::vec3(1.0f));

	glm::vec3 m_lightColor;
	glm::vec3 m_ambientColor;
	glm::vec3 m_diffuseColor;
	glm::vec3 m_specularColor;
};