#include "Components/TransformComponent.h"
#include "gtc/matrix_transform.hpp"

TransformComponent::TransformComponent()
{
	componentName = "Transform Component";
}

void TransformComponent::SetLocation(float x, float y, float z)
{
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void TransformComponent::SetScale(float x, float y, float z)
{
	//glm::mat4 identity = glm::mat4(1.0f);
	transform = glm::scale(transform, glm::vec3(x, y, z));
}

void TransformComponent::SetRotation(float roll, float pitch, float yaw)
{
	transform = glm::mat4(1.0f);
	transform = glm::rotate(transform, glm::radians(roll), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

void TransformComponent::AddOffstet(float x, float y, float z)
{
	transform[3].x = x;
	transform[3].y = y;
	transform[3].z = z;
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void TransformComponent::AddOffstet(const glm::vec3& newPosition)
{
	transform[3].x = newPosition.x;
	transform[3].y = newPosition.y;
	transform[3].z = newPosition.z;
	transform = glm::translate(transform, glm::vec3(newPosition.x, newPosition.y, newPosition.z));
}

void TransformComponent::AddScale(float x, float y, float z)
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
	transform *= scaleMatrix;
}

void TransformComponent::AddScale(glm::vec3& newScale)
{
	glm::vec3 existingScale = glm::vec3(transform[0][0], transform[1][1], transform[2][2]);
	glm::vec3 newIntScale = existingScale + newScale;

	// Create a new scale matrix with the updated scaling factors
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), newIntScale);

	// Multiply the existing model matrix by the new scale matrix
	transform = transform * scaleMatrix;
}

void TransformComponent::AddRotation(float Roll, float Pitch, float Yaw)
{
	if (Roll != 0)
		transform = glm::rotate(transform, glm::radians(Roll), glm::vec3(1.0f, 0.0f, 0.0f));
	if (Pitch != 0)
		transform = glm::rotate(transform, glm::radians(Pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	if (Yaw != 0)
		transform = glm::rotate(transform, glm::radians(Yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 &TransformComponent::GetLocation()
{
	return glm::vec3(transform[3]);
}