#include "Game/Lights/BaseLight.h"

BaseLight::BaseLight(glm::vec3 lightColor, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor) : GameEntity()
{
	m_lightColor = lightColor;
	m_ambientColor = ambientColor;
	m_diffuseColor = diffuseColor;
	m_specularColor = specularColor;
}

void BaseLight::ExtraDetailsWindow()
{
	ImGui::SeparatorText("Light Properties");
	ImGui::Text("LightColor:");
	ImGui::SameLine();

	ImGui::ColorEdit3("##LightColor", (float*)&m_diffuseColor, 0);

}
