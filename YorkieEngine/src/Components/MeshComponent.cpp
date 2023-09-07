#include "Components/MeshComponent.h"
#include "Graphics/Materials/Material.h"
#include "Graphics/Shaders/Shader.h"
#include "glad/glad.h"
#include <string>

Vertex::Vertex(const glm::vec3& position) : m_Position(position)
{
}

Vertex::Vertex(const glm::vec3& position, glm::vec3 normal) : m_Position(position), m_Normal(normal)
{

}

Vertex::Vertex(const glm::vec3& position, glm::vec3 normal, glm::vec2 textureCoordinates)
	: m_Position(position), m_Normal(normal), m_TextCoordinates(textureCoordinates)
{

}


MeshComponent::MeshComponent(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Material& material) : BaseComponent()
{
	m_material = &material;
	this->vertices = vertices;
	this->indices = indices;
	componentName = "MeshComponent";

	SetupVertexData();
}

MeshComponent::MeshComponent(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	SetupVertexData();
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
void MeshComponent::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.SetUniform1i(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].GetTextureID());
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void MeshComponent::DrawMesh(Shader& shader)
{
	glBindVertexArray(VAO);

	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to string
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to string
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to string

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.getProgramID(), (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].GetTextureID());
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}



void MeshComponent::SetupMesh()
{
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

	//Set the data to the gpu
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_TextCoordinates));


	// Unbind VAO (optional but recommended)
	glBindVertexArray(0);

	/*
	if (m_material)
	{
		//TODO: Harcoded for now, should be replaced when meses are loaded by a file.
		m_material->SetUVsCoordinate();
	}
	*/
}
