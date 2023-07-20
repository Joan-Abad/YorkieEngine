#pragma once
#include <vector>
#include <memory>
#include "../Shaders/Shader.h"

class YENGINE RenderObject
{
public: 
	RenderObject(const std::vector<float> vertices);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices, Shader shader);

	void Render();
	void CreateRenderObject();
	void AttachShader(Shader shader);
	void ExecuteShader();
	inline int GetVerticesSize() { return vertices.size(); };
	inline unsigned int GetIndicesSize() { return indices.size(); };

	inline int GetVAO() { return VAO; };
	inline int GetVBO() { return VBO; };

private: 

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader shader;
	//Almost 100% this doesn't go here
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};