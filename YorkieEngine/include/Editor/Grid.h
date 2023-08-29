#pragma once
#include "glm.hpp"
#include <vector>
#include "Graphics/Shaders/Shader.h"

class Grid
{
public:
	Grid();
	void DrawGrid();
	inline Shader& GetShader() { return *shader; };
private:
	unsigned int vao;
	int length;
	int quadSize;
	int slices;
	Shader* shader;
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec4> indices;
};
