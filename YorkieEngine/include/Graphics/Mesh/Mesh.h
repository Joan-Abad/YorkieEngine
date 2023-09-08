#pragma once
#include "Engine/YorkieEngine.h"
#include "Components/BaseComponent.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Materials/Material.h"
#include <vector>
#include <glm.hpp>

struct YorkieAPI Vertex {
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec2 m_TextCoordinates;
	
	Vertex(const glm::vec3& position);
	Vertex(const glm::vec3& position, glm::vec3 normal);
	Vertex(const glm::vec3& position, glm::vec3 normal, glm::vec2 textureCoordinates);
	Vertex() = default;
};

struct YorkieAPI Mesh : public BaseComponent
{
public:
	
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void PreUpdate(float deltaTime) override;
	void Draw();

	inline unsigned int GetVAO() { return VAO; };
	inline std::vector<unsigned int>& GetIndices() { return indices; };
	inline Material& GetMaterial() { return *m_material; };

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

private:
	void SetupVertexData();
	
	unsigned int VAO, VBO, EBO;

	/*Material that represents how the mesh is drawn.The mesh is a pointer, because one same mesh
	can be represented by the same material*/
	Material* m_material;
};