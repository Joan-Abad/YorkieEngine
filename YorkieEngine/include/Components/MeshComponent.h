#pragma once
#include "Engine/YorkieEngine.h"
#include "Components/BaseComponent.h"
#include <vector>
#include <glm.hpp>

class Material;

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
	MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material& material);
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void PreUpdate(float deltaTime) override;
	inline unsigned int GetVAO() { return VAO; };
	inline std::vector<unsigned int>& GetIndices() { return indices; };
	inline Material& GetMaterial() const { return *m_material; };
	//void DrawMesh();

protected:

private:
	void SetupVertexData();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
	//Material that represents the mesh
	Material* m_material;
};