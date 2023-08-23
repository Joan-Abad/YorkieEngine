#pragma once
#include <glm.hpp>

class TransformComponent
{
	glm::mat4 Transform{1.0f};
	
	operator glm::mat4& () { return Transform; };
	operator const glm::mat4& () const { return Transform; };
public:
	int i = 0; 
};