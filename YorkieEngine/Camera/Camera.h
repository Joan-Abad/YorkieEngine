#pragma once
#include "../Rendering/RenderObject.h"

class Camera : public RenderObject
{
public:
	Camera(const char* objectName);

	float pitch, yaw, roll;

	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::vec3 cameraRight;

	float FOV;

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

