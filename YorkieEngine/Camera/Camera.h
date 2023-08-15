#pragma once
#include "../Rendering/RenderObject.h"

class Camera : public RenderObject
{
public:
	Camera();

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::vec3 cameraRight;
	glm::mat4 view;

protected: 
	virtual void Draw(glm::mat4& view);
};

