#include "Camera/Camera.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Modules/CameraModule.h"

Camera::Camera(const char* objectName) : cameraTarget(glm::vec3(0.f, 0.f, 0.f)), cameraDirection(glm::vec3(0.f, 0.f, 0.f)),
cameraFront(glm::vec3(0.0f,0.0f,-1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90)
{
	view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	this->objectName = objectName;
	position = glm::vec3(0.0f, 0.0f, 25.0f);
	projection = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	nearPlane = 0.1f;
	farPlane = 400.f;
	FOV = 45.f;
}

void Camera::SetViewMatrix(glm::mat4 & matrix)
{
	view = matrix;
}

void Camera::SetProjectionMatrix(const float AspectRatio)
{
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(FOV), AspectRatio, nearPlane, farPlane);
}

