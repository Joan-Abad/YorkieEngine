#pragma once
#include <glm.hpp>

struct TransformComponent
{	
	void SetLocation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	operator glm::mat4& () { return transform; };
	operator const glm::mat4& () const { return transform; };

private:	
	
	glm::mat4 transform{ 1.0f };

};