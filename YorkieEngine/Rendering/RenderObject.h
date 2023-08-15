#pragma once
#include <vector>
#include "../YorkieEngine.h"
#include "../Shaders/Shader.h"
#include "glm.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
};

extern class Window;

//Object that can be rendered in the game world
class Yorkie RenderObject
{
	//class Window;
	friend class Window;
public: 
	RenderObject(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
	RenderObject(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader &shader);

	~RenderObject();

	virtual void Init();
	virtual void PreDraw();
	virtual void Draw();

	void AttachShader(Shader* shader);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(glm::vec3& newPosition);

	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);

	void AddRotation(float Roll, float Pitch, float Yaw);

	void SetPosition(float x, float y, float z);
	void SetPosition(glm::vec3 &newPosition);

	void SetRotation(float Roll, float Pitch, float Yaw);

	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 &newScale);

	void SetProjection();

	Window* window;

protected:
	//This constructor is for child objects. After setting vertices/indices or w/e you need, call SetupMesh(). 
	RenderObject() = default;


	//Transformations
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
	unsigned int VAO, VBO, EBO;

	void SetupMesh();

	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Shader* shader;

private:
	void SetUniformLocations();

};