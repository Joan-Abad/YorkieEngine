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
	GameEntity();

public:
	~GameEntity();

	std::string entityName;

	//Functions that you can implement on child actors of entity
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate();

	//Attach a new shader to the entity. This one will be used to draw the entity
	void AttachShader(Shader* shader);

	//Adds an offset to the current entity location
	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);

	//Adds a scale to the current entity scale
	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);

	//Adds a rotation to the current entity rotation
	void AddRotation(float Roll, float Pitch, float Yaw);

	//Sets a new entity location 
	void SetLocation(float x, float y, float z);
	void SetLocation(const glm::vec3 &newPosition);

	//Sets a new entity rotation
	void SetRotation(float Roll, float Pitch, float Yaw);

	//Sets a new entity scale
	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 &newScale);

	//Pointer that stores in which level this entity is in
	void SetViewport(Viewport* viewport);

	TransformComponent* RootComponent;

	//ECS (ENTT) helper functions
	//Adds a new component to the entity
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		auto& newComponent =  mViewport->registry.emplace<T>(entity, std::forward<Args>(args)...);
		components.push_back(&newComponent);
		return newComponent;
	}
	//Gets a component if it exists. 
	template <typename T>
	T& GetComponent()
	{
		return mViewport->registry.get<T>(entity);
	}
	//Check if an entity has a component
	template <typename T>
	bool HasComponent()
	{
		return mViewport->registry.any_of<T>(entity);
	}

	/////////////////////////////
	/// GETTERS
	////////////////////////////

	inline Shader& GetShader() { return *shader; };
	inline glm::vec3& GetPosition() { return RootComponent->GetPosition(); };
	inline glm::vec3& GetScale() { return RootComponent->GetScale(); };
	inline Rotator GetRotation() { return RootComponent->GetRotation(); };

	inline glm::mat4& GetModel() { return *RootComponent; };

protected:

private:
	Shader* shader;
	entt::entity entity;
	Viewport* mViewport;
	//List of the components of an entity
	std::vector<BaseComponent*> components;
	//Entity ID, used for now to give a defualt name to each entity
	static unsigned int entityID;
	void SetupEntity(Viewport* viewport);

};