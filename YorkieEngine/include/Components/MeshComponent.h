#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Components/TextureComponent.h"
#include "Engine/YorkieEngine.h"
#include <vector>


struct YorkieAPI Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;

	Vertex(const glm::vec3& position);
	Vertex() = default;
};

struct YorkieAPI MeshComponent : public BaseComponent
{
public:
	//MeshComponent(const std::vector<Vertex>& vertices);
	MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, TextureComponent* textureComponent = nullptr);
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void PreUpdate(float deltaTime) override;
	void DrawMesh();
private:
	void SetupVertexData();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
	TextureComponent* textureComponent;
};