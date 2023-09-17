#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Engine/YorkieEngine.h"

struct YorkieAPI Rotator {
    //Rotation around X
    float pitch = 0;
    //Rotation around Y
    float yaw = 0;
    //Rotation around Z
    float roll = 0;

    Rotator(float pitch, float yaw, float roll)
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

	void SetPosition(float x = 0, float y = 0, float z = 0);
	void SetScale(float x = 0, float y = 0, float z = 0);
	void SetRotation(float Roll = 0, float Pitch = 0, float Yaw = 0);

	void AddOffstet(float x = 0, float y = 0, float z = 0);
    void AddOffstet(const glm::vec3& newPosition);
	void AddScale(float x = 0, float y = 0, float z = 0);
    void AddScale(glm::vec3& newScale);
	void AddRotation(float Pitch = 0, float Yaw = 0, float Roll = 0);

	inline glm::vec3& GetPosition() { return position; };
    inline glm::vec3& GetScale() { return scale; };
    inline Rotator& GetRotation() { return rotation; };
    inline glm::mat4& GetModelMat4() { return modelMatrix; };

	operator glm::mat4& () { return modelMatrix; };
	operator const glm::mat4& () const { return modelMatrix; };
    Rotator rotation{ 0, 0, 0 };
    glm::vec3 position { 0.0f };
    glm::vec3 scale { 1.0f };

    glm::mat4 rotationMatrix { 1.0f };
    glm::mat4 scaleMatrix { 1.0f };
    glm::mat4 translationMatrix { 1.0f };
    glm::mat4 modelMatrix { 1.0f };
private:	
	

    void UpdateModelMatrix();

	
};