#pragma once
#include "Game/GameEntity.h"

class Camera : public GameEntity
{
	friend class Viewport;
public:
	float FOV;

	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	void SetCameraDirections();
	void SetViewMatrix(glm::mat4& matrix);
	void SetProjectionMatrix(const float AspectRatio);
	inline glm::mat4& GetProjection() { return projection; };
	inline glm::mat4& GetView() { return view; };
	inline float GetNearPlane() { return nearPlane; };
	inline float GetFarPlane() { return farPlane; };

protected: 
	//Functions that you can implement on child actors of entity
	virtual void Init() override;
	//virtual void Update(float deltaTime);
	//virtual void PostUpdate();
private:
	Camera(Viewport* viewport);
	float nearPlane;
	float farPlane;
	glm::mat4 view;
	glm::mat4 projection;
};

