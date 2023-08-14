#pragma once
#include <vector>
#include "../YorkieEngine.h"
#include "../Shaders/Shader.h"
#include "Buffers/VAO.h"
#include "Buffers/VBO.h"
#include "glm.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
};

class Yorkie RenderObject
{
	friend class Window;
public: 
	RenderObject(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~RenderObject();
	virtual void Draw();
	void AttachShader(Shader* shader);
protected:
	RenderObject() = default;

	unsigned int VAO, VBO, EBO;
	void SetupMesh();

	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

	Shader* shader;
private: 
};