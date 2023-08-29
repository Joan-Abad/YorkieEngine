#pragma once
#include "Game/GameEntity.h"

class Camera : public GameEntity
{
public:
	Camera(Viewport* viewport);

	float FOV;
	float pitch, yaw, roll;

	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	void SetViewMatrix(glm::mat4& matrix);
	void SetProjectionMatrix(const float AspectRatio);
	inline glm::mat4& GetProjection() { return projection; };
	inline glm::mat4& GetView() { return view; };

private:
	float nearPlane;
	float farPlane;
	glm::mat4 view;
	glm::mat4 projection;
};

