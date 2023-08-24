#pragma once
#include <glad/glad.h>
#include <vector>
#include <iostream>

enum class Data_Type : int
{
	YE_FLOAT = 0x1406,
	YE_DOUBLE = 0x140A,
	YE_CHAR = 0x1400,
	YE_UCHAR = 0x1401,
	YE_SHORT = 0x1402,
	YE_USHORT = 0x1403,
	YE_INT = 0x1404,
	YE_UINT = 0x1405
};

class Buffer
{
public:
	Buffer() = default;
	~Buffer();


protected:

	unsigned int ID;

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