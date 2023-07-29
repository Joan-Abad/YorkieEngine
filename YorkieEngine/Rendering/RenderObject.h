#pragma once
#include <vector>
#include "../YorkieEngine.h"
#include "../Shaders/Shader.h"
#include "Buffers/VAO.h"
#include "Buffers/VBO.h"


class Yorkie RenderObject
{
	friend class Window;
public: 
	RenderObject();
	~RenderObject();

	void AttachShader(Shader shader);
	void AddVBOBuffer(VBO& vbo);
	void Render();

private: 
	VAO vao;
	std::vector<VBO*> vbos;

	Shader shader;
	//Almost 100% this doesn't go here
	unsigned int shaderProgram;
	void CreateShaderProgram();
	void ExecuteShader();

public: 
	inline unsigned int &GetVAO() { return vao.GetVAO(); }
};