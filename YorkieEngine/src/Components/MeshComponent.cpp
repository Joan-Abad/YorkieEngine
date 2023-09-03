#include "Components/MeshComponent.h"
#include "glad/glad.h"

Vertex::Vertex(const glm::vec3& position)
{
	m_Position = position;
}

Vertex::Vertex(const glm::vec3& position, glm::vec3 normal)
{
	m_Position = position;
	m_Normal = normal;
}

MeshComponent::MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, TextureComponent* textureComponent, TextureComponent* specularComponent)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textureComponent = nullptr;
	this->specularComponent = nullptr;
	componentName = "MeshComponent";
	SetupVertexData();
	
	if (textureComponent)
	{
		textureComponent->SetTextureData();
		this->textureComponent = textureComponent;
	}
	if (specularComponent)
	{
		this->specularComponent = specularComponent;
	}
	glBindVertexArray(0);
}

void MeshComponent::Start()
{
}

void MeshComponent::Update(float deltaTime)
{
}

void MeshComponent::PreUpdate(float deltaTime)
{

}

void MeshComponent::DrawMesh()
{
	glBindVertexArray(VAO);

	if (textureComponent)
	{
		// Activate the appropriate texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureComponent->GetTextureID());
		textureComponent->GetShader().SetUniform1i("material.diffuse", 0);
	}
	if (specularComponent)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularComponent->GetTextureID());
		textureComponent->GetShader().SetUniform1i("material.specular", 1);
	}
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Position));

	// Vertex normals (assuming Vertex structure contains position and normal)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Normal));

	// Unbind VAO (optional but recommended)
}
