#pragma once
#include <vector>
#include "../YorkieEngine.h"
#include "../Shaders/Shader.h"
#include "glm.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	
	Vertex(const glm::vec3& position)
	{
		Position = position;
	}
};

extern class Window;

//Object that can be rendered in the game world
class Yorkie RenderObject
{
	//class Window;
	friend class Window;

public: 
	RenderObject(const char* objectName, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
	RenderObject(const char* objectName, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, Shader &shader);

	~RenderObject();

	virtual void Init();
	virtual void PreDraw();
	virtual void Draw();

	void AttachShader(Shader* shader);

	void AddOffstet(float x, float y, float z);
	void AddOffstet(const glm::vec3& newPosition);

	void AddScale(float x, float y, float z);
	void AddScale(glm::vec3& newScale);

	void AddRotation(float Roll, float Pitch, float Yaw);

	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3 &newPosition);

	void SetRotation(float Roll, float Pitch, float Yaw);

	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 &newScale);

	Shader& GetShader() { return *shader; };

	Window* window;
	const char* objectName;
	//TODO: Remove from here, not public
	glm::vec3 position;

	glm::vec3 GetPosition() { return position; };
	inline glm::mat4& GetModel() { return model; };

protected:
	//This constructor is for child objects. After setting vertices/indices or w/e you need, call SetupMesh(). 
	RenderObject() = default;


	//Transformations
	glm::mat4 model;

	GLint modelLoc;
	unsigned int VAO, VBO, EBO;

	void SetupMesh();

	// mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Shader* shader;
};