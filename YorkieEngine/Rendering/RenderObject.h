#pragma once
#include <vector>
#include <memory>
#include "../Shaders/Shader.h"
#include "../Buffer.h"

class YENGINE RenderObject
{
public: 
	RenderObject(const char* meshPath, Shader shader);
	RenderObject(const std::vector<float> vertices, Shader shader);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices);
	RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices, Shader shader);
	~RenderObject();

	void Render();
	
	void AttachShader(Shader shader);
	Buffer buffer;

private: 

	Shader shader;
	//Almost 100% this doesn't go here
	unsigned int shaderProgram;

	void CreateShaderProgram();
	void ExecuteShader();

};