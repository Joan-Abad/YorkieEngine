#include "Camera/Camera.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Modules/CameraModule.h"
#include "Graphics/Renderer.h"
Camera::Camera(Viewport* viewport) : GameEntity(viewport),
	cameraTarget(glm::vec3(0.f, 0.f, 0.f)),
	cameraDirection(glm::vec3(0.f, 0.f, 0.f)),
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
	cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	nearPlane(0.1f), farPlane(400.f), FOV(45.f),
	projection(glm::mat4(1.0f)),
	pitch(-25), roll(0), yaw(-90)
{
	position = glm::vec3(0.0f, 10.0f, 25.0f);
	view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	this->entityName = "Camera";
	cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	cameraUp = glm::normalize(glm::cross(cameraRight, front));
	
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

