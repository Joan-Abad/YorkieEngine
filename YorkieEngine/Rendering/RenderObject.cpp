#include "RenderObject.h"
#include "glad/glad.h"
#include "RenderingSystem.h"
#include <sstream>
#include <vector>
#include <glm.hpp>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../Window/Public/Window.h"
#include "../Modules/ShaderModule.h"

RenderObject::RenderObject(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices)
{
	this->vertices = vertices;
	this->indices = indices;
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	shader = nullptr;
	window = nullptr;
	SetupMesh();
}

RenderObject::RenderObject(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader &shader) : RenderObject(vertices, indices)
{
	this->shader = &shader;
}

RenderObject::~RenderObject()
{
}

void RenderObject::Init()
{
	if (!shader)
		shader = ShaderModule::GetShaderModule()->GetDefaultShader();

	SetUniformLocations();
}

void RenderObject::PreDraw()
{
	//AddOffstet(0, 0, -0.1f);
	
	SetPosition(0,0,-3);
	//AddRotation(0.f, 1.f, 0.f);
	SetScale(2.5f, 1.0f, 1.0);
	SetProjection();

	shader->ExecuteShader();
	// Set uniforms
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	shader->StopShader();
}

void RenderObject::SetupMesh()
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

void RenderObject::Draw()
{

	shader->ExecuteShader();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}

void RenderObject::SetUniformLocations()
{
	shader->ExecuteShader();
	modelLoc = glGetUniformLocation(shader->getProgramID(), "model");
	viewLoc = glGetUniformLocation(shader->getProgramID(), "view");
	projLoc = glGetUniformLocation(shader->getProgramID(), "projection");
	shader->StopShader();
}

void RenderObject::AttachShader(Shader* shader)
{
    this->shader = shader;
}

void RenderObject::AddOffstet(float x, float y, float z)
{
	view = glm::translate(view, glm::vec3(x, y, z));
}

void RenderObject::AddOffstet(glm::vec3& newPosition)
{
	view = glm::translate(view, glm::vec3(newPosition.x, newPosition.y, newPosition.z));
}

void RenderObject::AddScale(float x, float y, float z)
{
	model = glm::scale(model, glm::vec3(x, y, z));
}

void RenderObject::AddScale(glm::vec3& newScale)
{
	model = glm::scale(model, newScale);
}

void RenderObject::AddRotation(float Roll, float Pitch, float Yaw)
{
	if(Roll != 0)
		model = glm::rotate(model, glm::radians(Roll), glm::vec3(1.0f, 0.0f, 0.0f));
	if(Pitch != 0)
		model = glm::rotate(model, glm::radians(Pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	if(Yaw != 0)
		model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 0.0f, 1.0f));
}

void RenderObject::SetPosition(glm::vec3& newPosition)
{
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(newPosition.x, newPosition.y, newPosition.z));
}

void RenderObject::SetPosition(float x, float y, float z)
{
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(x, y, z));
}

void RenderObject::SetRotation(float Roll, float Pitch, float Yaw)
{
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(Roll), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Pitch), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Yaw), glm::vec3(0.0f, 0.0f, 1.0f));	
}

void RenderObject::SetScale(float x, float y, float z)
{
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(x, y, z));
}

void RenderObject::SetScale(glm::vec3& newScale)
{
	model = glm::scale(model, glm::vec3(newScale.x, newScale.y, newScale.z));
}

void RenderObject::SetProjection()
{
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)window->GetWindowWidth() / (float)window->GetWindowHeight(), 0.1f, 400.0f);
}
