#include "Graphics/Mesh/Mesh.h"
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

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	
	Shader* shader = new Shader("res/shaders/defaultGameEntity.shader");
	m_material = new Material(shader);
	

	SetupVertexData();
}

void Mesh::Start()
{
}

void Mesh::Update(float deltaTime)
{
}

void Mesh::PreUpdate(float deltaTime)
{

}
void Mesh::Draw()
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	bool textureTypeSupported = false;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
			textureTypeSupported = true;
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
			textureTypeSupported = true;
		}
		if (textureTypeSupported)
		{
			std::string uniformName = "material." + name + number;
			m_material->m_Shader->SetUniform1i(uniformName.c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].GetTextureID());
		}
	}
	glActiveTexture(GL_TEXTURE0);

	m_material->m_Shader->SetUniform1f("material.shininess", m_material->GetShininess());

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Mesh::SetupVertexData()
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
