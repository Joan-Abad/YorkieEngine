#pragma once
#include <vector>
#include <memory>
#include "../Shaders/Shader.h"

class YENGINE RenderObject
{
public: 
	RenderObject(const char* meshPath, Shader shader);
	RenderObject(const std::vector<float> vertices, Shader shader);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices, Shader shader);
	~RenderObject();

	void Render();
	void CreateRenderObject();
	
	void AttachShader(Shader shader);
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

	void CreateShaderProgram();
	void ExecuteShader();

};