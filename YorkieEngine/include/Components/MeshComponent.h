#pragma once
#include "Engine/YorkieEngine.h"
#include "Components/BaseComponent.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Texture/Texture.h"
#include <vector>
#include <glm.hpp>

class Material;

struct YorkieAPI Vertex {
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec2 m_TextCoordinates;
	
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, glm::vec3 normal);
	Vertex(const glm::vec3& position, glm::vec3 normal, glm::vec2 textureCoordinates);
	Vertex() = default;
};

struct YorkieAPI MeshComponent : public BaseComponent
{
public:
	MeshComponent() = default;
	//MeshComponent(const std::vector<Vertex>& vertices);
	MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material& material);
	MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void PreUpdate(float deltaTime) override;
	void DrawMesh(Shader& shader);
	inline unsigned int GetVAO() { return VAO; };
	inline std::vector<unsigned int>& GetIndices() { return indices; };
	inline Material& GetMaterial() const { return *m_material; };
	void Draw(Shader& shader);

protected:

private:
	void SetupMesh();
	void SetupVertexData();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO, VBO, EBO;
	unsigned int m_TextureCoordsBO;
	//Material that represents the mesh
	Material* m_material;
};