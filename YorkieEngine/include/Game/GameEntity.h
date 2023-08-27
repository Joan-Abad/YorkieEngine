#pragma once
#include <vector>
#include "Engine/YorkieEngine.h"
#include "Graphics/Shaders/Shader.h"
#include "glm.hpp"
#include "entt/entt.hpp"
#include "Window/Viewport.h"
#include "Components/TransformComponent.h"


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	
	Vertex(const glm::vec3& position)
	{
		Position = position;
	}
};

class YorkieAPI GameEntity
{
	friend class Viewport;
public: 
	GameEntity();
	GameEntity(const char* objectName, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	GameEntity(const char* objectName, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Shader& shader);

public:
	~GameEntity();

	virtual void Init();
	virtual void PreDraw();
	virtual void Draw();

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
		return viewport->registry.emplace<T>(entity, std::forward<Args>(args)...);
	}

	template <typename T>
	T& GetComponent()
	{
		return viewport->registry.get<T>(entity);
	}

	template <typename T>
	T& HasComponent()
	{
		return viewport->registry.any_of<T>(entity);
	}

	inline Shader& GetShader() { return *shader; };

	const char* objectName;
	//TODO: Remove from here, not public
	glm::vec3 position;
	Viewport* viewport = nullptr;

	glm::vec3 &GetEntityLocation();
	inline glm::mat4& GetModel() { return model; };

protected:

	//Transformations
	glm::mat4 model;

	GLint modelLoc;
	Shader* shader = nullptr;
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
	void SetupMesh();

private:
	entt::entity entity;
};