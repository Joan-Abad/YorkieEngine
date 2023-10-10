#pragma once
#include <vector>
#include "Engine/YorkieEngine.h"
#include "Graphics/Shaders/Shader.h"
#include "glm.hpp"
#include "entt/entt.hpp"
#include "Window/Viewport.h"
#include "Components/TransformComponent.h"
#include "Game/Level.h"

class PointLight;

class YorkieAPI GameEntity
{
	friend class Viewport;
	friend class LevelEditor;
	friend class Level;
public:
	GameEntity();

public:
	~GameEntity();

	std::string entityName;

	//Functions that you can implement on child actors of entity
	virtual void OnConstruct();
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
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& newPosition);


	//Callbacks that will be called when the position is set manually. 
	using OnSetPositionCallback = int(*)(int, double);
	std::vector<OnSetPositionCallback> m_SetPositionCallbacks;

	//Sets a new entity rotation
	void SetRotation(float Roll, float Pitch, float Yaw);

	//Sets a new entity scale
	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3& newScale);

	//Pointer that stores in which level this entity is in
	void SetViewport(Level& level);

	TransformComponent* RootComponent;
	//TODO: REMOVE
	PointLight* m_PointLight;

	//ECS (ENTT) helper functions
	//Adds a new component to the entity
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		auto& newComponent = m_Level->registry.emplace<T>(entity, std::forward<Args>(args)...);
		components.push_back(&newComponent);
		return newComponent;
	}
	//Gets a component if it exists. 
	template <typename T>
	T& GetComponent()
	{
		return m_Level->registry.get<T>(entity);
	}
	//Check if an entity has a component
	template <typename T>
	bool HasComponent()
	{
		return m_Level->registry.any_of<T>(entity);
	}

	/////////////////////////////
	/// GETTERS
	////////////////////////////

	inline Shader& GetShader() { return *shader; };
	inline glm::vec3& GetPosition() { return RootComponent->GetPosition(); };
	inline glm::vec3& GetScale() { return RootComponent->GetScale(); };
	inline Rotator GetRotation() { return RootComponent->GetRotation(); };
	inline bool GetCanDrawAxis() { return m_CanDrawAxis; };
	inline glm::mat4& GetModel() { return *RootComponent; };

protected:
	bool m_CanDrawAxis;
	Level* m_Level;
	virtual void ExtraDetailsWindow();

private:
	Shader* shader;
	entt::entity entity;
	//List of the components of an entity
	std::vector<BaseComponent*> components;

	//Entity ID, used for now to give a defualt name to each entity
	static unsigned int entityID;
	void SetupEntity(Level& level);

};
