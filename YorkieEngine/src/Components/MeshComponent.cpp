#include "Components/MeshComponent.h"
#include "glad/glad.h"

Vertex::Vertex(const glm::vec3& position)
{

	Position = position;

}

MeshComponent::MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
	this->vertices = vertices;
	this->indices = indices;
	componentName = "MeshComponent";
	SetupVertexData();
}

void MeshComponent::Start()
{
}

void MeshComponent::Update(float deltaTime)
{
}

void MeshComponent::DrawMesh()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void MeshComponent::SetupVertexData()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO and VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Transfer vertex data to the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	// Bind EBO and transfer index data to the buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Set up vertex attributes
	// Vertex positions (assuming Vertex structure contains position and normal)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	// Vertex normals (assuming Vertex structure contains position and normal)
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	// Unbind VAO (optional but recommended)
	glBindVertexArray(0);
}
