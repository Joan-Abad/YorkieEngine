#include "Camera.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../Modules/CameraModule.h"

Camera::Camera() : cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraTarget(glm::vec3(0.f, 0.f, 0.f)), cameraDirection(glm::vec3(0.f, 0.f, 0.f)),
cameraFront(glm::vec3(0.0f,0.0f,-1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90)
{
	view = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

void Camera::Draw(glm::mat4& view)
{

}
