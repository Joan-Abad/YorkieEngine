#include "Components/TransformComponent.h"
#include "gtc/matrix_transform.hpp"

TransformComponent::TransformComponent()
{
	componentName = "Transform Component";
}

void TransformComponent::Update(float deltaTime)
{
	
}

void TransformComponent::PostUpdate(float deltaTime)
{

}

void TransformComponent::SetPosition(float x, float y, float z)
{
	position = glm::vec3(x,y,z);
	UpdateModelMatrix();
}

void TransformComponent::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
	UpdateModelMatrix();
}

void TransformComponent::SetRotation(float Pitch, float Yaw, float Roll)
{
	rotation = Rotator(Pitch, Yaw, Roll);
	UpdateModelMatrix();
}

void TransformComponent::AddOffstet(float x, float y, float z)
{
	position += glm::vec3(x, y, z);
	UpdateModelMatrix();
}

void TransformComponent::AddOffstet(const glm::vec3& newPosition)
{
	position += newPosition;
	UpdateModelMatrix();
}

void TransformComponent::AddScale(float x, float y, float z)
{
	scale += glm::vec3(x,y,z);
	UpdateModelMatrix();
}

void TransformComponent::AddScale(glm::vec3& newScale)
{
	scale += newScale;
	UpdateModelMatrix();
}

void TransformComponent::AddRotation(float Pitch, float Yaw, float Roll)
{
	rotation += Rotator(Pitch, Yaw, Roll);
	UpdateModelMatrix();
}

void TransformComponent::UpdateModelMatrix()
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.roll), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, scale);
}
