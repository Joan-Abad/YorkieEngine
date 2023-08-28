#pragma once
#include <vector>
#include "Engine/YorkieEngine.h"
#include "Graphics/Shaders/Shader.h"
#include "glm.hpp"
#include "entt/entt.hpp"
#include "Window/Viewport.h"
#include "Components/TransformComponent.h"

class YorkieAPI GameEntity
{
	friend class Viewport;
public: 
	GameEntity(Viewport* viewport);
	GameEntity(const char* objectName);
	GameEntity(const char* objectName, Shader& shader);

public:
	~GameEntity();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate();

	void AttachShader(Shader* shader);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);

	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);

	void AddRotation(float Roll, float Pitch, float Yaw);

	void SetEntityLocation(float x, float y, float z);
	void SetEntityLocation(const glm::vec3 &newPosition);

	void SetRotation(float Roll, float Pitch, float Yaw);

	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 &newScale);

	void SetViewport(Viewport* viewport);

	TransformComponent* RootComponent = nullptr;

	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		auto& newComponent =  mViewport->registry.emplace<T>(entity, std::forward<Args>(args)...);
		components.push_back(&newComponent);
		return newComponent;
	}

	template <typename T>
	T& GetComponent()
	{
		return mViewport->registry.get<T>(entity);
	}

	template <typename T>
	T& HasComponent()
	{
		return mViewport->registry.any_of<T>(entity);
	}

	inline Shader& GetShader() { return *shader; };

	const char* objectName;
	//TODO: Remove from here, not public
	glm::vec3 position;
	Viewport* mViewport = nullptr;

	glm::vec3 &GetEntityLocation();
	inline glm::mat4& GetModel() { return *RootComponent; };

protected:

	//Transformations
	glm::mat4 model;

	GLint modelLoc;
	Shader* shader = nullptr;
	// mesh data
	
private:
	std::vector<BaseComponent*> components;
	entt::entity entity;
};