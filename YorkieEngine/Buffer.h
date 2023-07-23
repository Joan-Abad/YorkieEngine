#pragma once
#include <glad/glad.h>
#include <vector>
#include <iostream>

class Buffer
{
public:
	Buffer();
	~Buffer();

	template<typename T>
	void AddBufferData(std::vector<T> data)
	{
		// Bind the VAO
		glBindVertexArray(VAO);
		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//Add data to the buffer
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

		//Declare layout
		GLenum type = GetGLType<T>();
		glVertexAttribPointer(layoutAttributeIndex, 3, type, GL_FALSE, 3* sizeof(T), 0);
		glEnableVertexAttribArray(layoutAttributeIndex);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		layoutAttributeIndex++;
	}

	inline GLuint GetVAO() { return VAO; }

private:
	GLuint VBO;
	GLuint VAO;
	unsigned int layoutAttributeIndex;

private:
	// Helper function to convert the template type T to GLenum
	template<typename T>
	GLenum GetGLType();

	// Template specialization for GL_FLOAT
	template <>
	GLenum GetGLType<float>()
	{
		return GL_FLOAT;
	}

	// Template specialization for GL_DOUBLE
	template <>
	GLenum GetGLType<double>()
	{
		return GL_DOUBLE;
	}

	// Template specialization for GL_BYTE
	template <>
	GLenum GetGLType<char>()
	{
		return GL_BYTE;
	}

	// Template specialization for GL_UNSIGNED_BYTE
	template <>
	GLenum GetGLType<unsigned char>()
	{
		return GL_UNSIGNED_BYTE;
	}

	// Template specialization for GL_SHORT
	template <>
	GLenum GetGLType<short>()
	{
		return GL_SHORT;
	}

	// Template specialization for GL_UNSIGNED_SHORT
	template <>
	GLenum GetGLType<unsigned short>()
	{
		return GL_UNSIGNED_SHORT;
	}

	// Template specialization for GL_INT
	template <>
	GLenum GetGLType<int>()
	{
		return GL_INT;
	}

	// Template specialization for GL_UNSIGNED_INT
	template <>
	GLenum GetGLType<unsigned int>()
	{
		return GL_UNSIGNED_INT;
	}
};