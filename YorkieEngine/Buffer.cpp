#include "Buffer.h"

Buffer::Buffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	layoutAttributeIndex = 0; 
}

Buffer::~Buffer()
{
}
