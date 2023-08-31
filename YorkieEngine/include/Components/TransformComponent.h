#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Engine/YorkieEngine.h"

struct YorkieAPI TransformComponent : BaseComponent
{	
public:
	TransformComponent();

	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);

	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);
	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);
	void AddRotation(float Roll, float Pitch, float Yaw);

	glm::vec3& GetPosition() { return position; };
	glm::vec3& GetScale() { return scale; };
	glm::vec3& GetRotation() { return rotation; };
	glm::mat4& GetModelMat4() { return modelMatrix; };

	operator glm::mat4& () { return modelMatrix; };
	operator const glm::mat4& () const { return modelMatrix; };

private:	
	
	glm::vec3 position { 0.0f };
	glm::vec3 scale { 1.0f };
	glm::vec3 rotation { 0.0f };
	glm::mat4 modelMatrix { 1.0f };
	void UpdateModelMatrix();
};