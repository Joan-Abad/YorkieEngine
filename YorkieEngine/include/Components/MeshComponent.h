#pragma once
#include <glm.hpp>
#include "Components/BaseComponent.h"
#include "Components/TextureComponent.h"
#include "Engine/YorkieEngine.h"
#include <vector>


struct YorkieAPI Vertex {
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, glm::vec3 normal);
	Vertex() = default;
};

struct YorkieAPI MeshComponent : public BaseComponent
{
public:
	//MeshComponent(const std::vector<Vertex>& vertices);
	MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, TextureComponent* textureComponent = nullptr, TextureComponent* specularComponent = nullptr);
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void PreUpdate(float deltaTime) override;
	void DrawMesh();

	void SetTextureComponent(TextureComponent& textureComponent);
protected:
private:
	void SetupVertexData();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
	TextureComponent* textureComponent;
	TextureComponent* specularComponent;
};