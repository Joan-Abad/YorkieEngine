#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Engine/YorkieEngine.h"

struct YorkieAPI TransformComponent : BaseComponent
{	
public:
	TransformComponent();
	void SetLocation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);
	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);
	void AddRotation(float Roll, float Pitch, float Yaw);

	glm::vec3 &GetLocation();

	glm::mat4& GetMat4() { return transform; };
	operator glm::mat4& () { return transform; };
	operator const glm::mat4& () const { return transform; };

private:	
	
	glm::mat4 transform{ 1.0f };

};