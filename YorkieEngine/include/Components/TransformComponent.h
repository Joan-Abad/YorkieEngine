#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Engine/YorkieEngine.h"

struct YorkieAPI Rotator {
    float roll = 0;
    float pitch = 0;
    float yaw = 0;

    Rotator(float roll, float pitch, float yaw)
        : roll(roll), pitch(pitch), yaw(yaw) {
    }

    Rotator operator+(const Rotator& rhs) const {
        return Rotator(roll + rhs.roll, pitch + rhs.pitch, yaw + rhs.yaw);
    }

    Rotator operator-(const Rotator& rhs) const {
        return Rotator(roll - rhs.roll, pitch - rhs.pitch, yaw - rhs.yaw);
    }

    Rotator& operator+=(const Rotator& rhs) {
        roll += rhs.roll;
        pitch += rhs.pitch;
        yaw += rhs.yaw;
        return *this;
    }

    Rotator& operator-=(const Rotator& rhs) {
        roll -= rhs.roll;
        pitch -= rhs.pitch;
        yaw -= rhs.yaw;
        return *this;
    }
};


struct YorkieAPI TransformComponent : BaseComponent
{	
public:
	TransformComponent();

	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);

	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float Roll, float Pitch, float Yaw);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);
	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);
	void AddRotation(float Roll, float Pitch, float Yaw);

	inline glm::vec3& GetPosition() { return position; };
    inline glm::vec3& GetScale() { return scale; };
    inline Rotator& GetRotation() { return rotation; };
    inline glm::mat4& GetModelMat4() { return modelMatrix; };

	operator glm::mat4& () { return modelMatrix; };
	operator const glm::mat4& () const { return modelMatrix; };

private:	
	
	glm::vec3 position { 0.0f };
	glm::vec3 scale { 1.0f };
	Rotator rotation{ 0, 0, 0 };
    glm::mat4 modelMatrix { 1.0f };
    void UpdateModelMatrix();

	
};