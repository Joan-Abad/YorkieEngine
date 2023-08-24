#include "Components/TransformComponent.h"
#include "gtc/matrix_transform.hpp"

void TransformComponent::SetLocation(float x, float y, float z)
{
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void TransformComponent::SetScale(float x, float y, float z)
{
	//transform = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(x, y, z));
}

void TransformComponent::SetRotation(float roll, float pitch, float yaw)
{
	//transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(roll), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}
