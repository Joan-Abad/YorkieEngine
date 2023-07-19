#pragma once
#include <vector>
#include <memory>
#include "../Shaders/Shader.h"

class YENGINE RenderObject
{
public: 
	RenderObject(const std::vector<float> vertices);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices);

	void Render();
	void AttachVertexShader(Shader vertexShader);
	void AttachFragmentShader(Shader fragmentShader);

	inline int GetVerticesSize() { return vertices.size(); };
	inline int GetVAO() { return VAO; };
	inline int GetVBO() { return VBO; };
private: 

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader vertexShader;
	Shader fragmentShader;
	//Almost 100% this doesn't go here
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int VBO;

};