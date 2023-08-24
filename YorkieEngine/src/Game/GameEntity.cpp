#include "Game/GameEntity.h"
#include "glad/glad.h"
#include <sstream>
#include <vector>
#include <glm.hpp>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Window/Window.h"
#include "Modules/ShaderModule.h"
#include <iostream>
#include "Window/Viewport.h"

GameEntity::GameEntity(const char* objectName, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
	this->vertices = vertices;
	this->indices = indices;
	model = glm::mat4(1.0f);
	position = glm::vec3(0,0,0);
	shader = nullptr;
	viewport = nullptr;
	
	this->objectName = objectName;
	SetupMesh();
}

GameEntity::GameEntity(const char* objectName, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader &shader) : GameEntity(objectName, vertices, indices)
{
	this->shader = &shader;
}

GameEntity::~GameEntity()
{
}


void GameEntity::Init()
{
	if (!shader)
		shader = ShaderModule::GetShaderModule()->GetDefaultShader();
}



void GameEntity::PreDraw()
{

}

void GameEntity::SetupMesh()
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

void GameEntity::Draw()
{	
	//TODO: Remove from here
	glm::vec3 position = glm::vec3(model[3]); // The fourth column (if using column-major)

	// The 'position' vector now contains the x, y, and z coordinates of the object in world space
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void GameEntity::AttachShader(Shader* shader)
{
    this->shader = shader;
}

void GameEntity::AddOffstet(float x, float y, float z)
{
	model = glm::translate(model, glm::vec3(x, y, z));
}

void GameEntity::AddOffstet(const glm::vec3& newPosition)
{
	position += newPosition;
}

void GameEntity::AddScale(float x, float y, float z)
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(x,y,z));
	model *= scaleMatrix;
}

void GameEntity::AddScale(glm::vec3& newScale)
{
	glm::vec3 existingScale = glm::vec3(model[0][0], model[1][1], model[2][2]);
	glm::vec3 newIntScale = existingScale + newScale;

	// Create a new scale matrix with the updated scaling factors
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), newIntScale);

	// Multiply the existing model matrix by the new scale matrix
	model = model * scaleMatrix;

	// Print the resulting transformation matrix
	const float* matData = glm::value_ptr(model);
	for (int i = 0; i < 16; ++i) {
		std::cout << matData[i] << " ";
		if ((i + 1) % 4 == 0)
			std::cout << std::endl;
	}
}

void GameEntity::AddRotation(float Roll, float Pitch, float Yaw)
{
	if(Roll != 0)
		model = glm::rotate(model, glm::radians(Roll), glm::vec3(1.0f, 0.0f, 0.0f));
	if(Pitch != 0)
		model = glm::rotate(model, glm::radians(Pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	if(Yaw != 0)
		model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

void GameEntity::SetPosition(const glm::vec3& newPosition)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(newPosition.x, newPosition.y, newPosition.z));
}

void GameEntity::SetPosition(float x, float y, float z)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, z));
}

void GameEntity::SetRotation(float Roll, float Pitch, float Yaw)
{
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(Roll), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 0.0f, 1.0f));	
}

void GameEntity::SetScale(float x, float y, float z)
{
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(x, y, z));
}

void GameEntity::SetScale(glm::vec3& newScale)
{
	model = glm::scale(model, glm::vec3(newScale.x, newScale.y, newScale.z));
}

void GameEntity::SetViewport(Viewport* viewport)
{
	this->viewport = viewport;
}
