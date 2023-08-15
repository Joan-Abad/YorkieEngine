#pragma once
#include "../Rendering/RenderObject.h"

class Camera : public RenderObject
{
public:
	Camera();

	float pitch, yaw, roll;

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 direction;

	glm::vec3 cameraRight;
	glm::mat4 view;

protected: 
	virtual void Draw(glm::mat4& view);
};

