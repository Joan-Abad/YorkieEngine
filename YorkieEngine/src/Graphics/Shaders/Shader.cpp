#include "Graphics/Shaders/Shader.h"
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "gtc/type_ptr.hpp"
#include "Logging/Logger.h"

Shader::Shader(const char* shaderPath)
{
	ParseShader(shaderPath);
	
	//Vertex shader init
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSourcePtr = shaderProgramSource.VertexSource.c_str();
	glShaderSource(vertexShaderID, 1, &vertexShaderSourcePtr, nullptr);
	glCompileShader(vertexShaderID);
    CheckShaderCompilationStatus(vertexShaderID);

	//Fragment shader init
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSourcePtr = shaderProgramSource.FragmentSource.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSourcePtr, nullptr);
	glCompileShader(fragmentShaderID);
	CheckShaderCompilationStatus(fragmentShaderID);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);
	int  success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Info log:" << infoLog;
	}
}

void Shader::CheckShaderCompilationStatus(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, errorLog.data());
        std::cerr << "Shader compilation failed:\n" << errorLog.data() << std::endl;
    }
}

void Shader::ParseShader(const std::string& path)
{
	auto a = GL_FRAGMENT_SHADER;
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(path);
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			if (type != ShaderType::NONE)
				ss[static_cast<int>(type)] << line << '\n';
		}

	}

	shaderProgramSource = { ss[0].str(), ss[1].str() };
}

void Shader::Bind()
{
	glUseProgram(ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

/////////////////////////////////////////
///			UNIFORM INTEGERS		  ///
/////////////////////////////////////////


void Shader::SetUniform1i(const char* variableName, const int i)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform1i(loc, i);
}

void Shader::SetUniform2i(const char* variableName, const int i1, const int i2)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform2i(loc, i1, i2);
}

void Shader::SetUniform3i(const char* variableName, const int i1, const int i2, const int i3)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform3i(loc, i1, i2, i3);
}

void Shader::SetUniform4i(const char* variableName, const int i1, const int i2, const int i3, const int i4)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform4i(loc, i1, i2, i3, i4);
}

/////////////////////////////////////////
///		UNIFORM UNSIGNED INTEGERS	  ///
/////////////////////////////////////////

void Shader::SetUniform1ui(const char* variableName, const unsigned int ui)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform1ui(loc, ui);
}

void Shader::SetUniform2ui(const char* variableName, const unsigned int ui1, const unsigned int ui2)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform2ui(loc, ui1, ui2);
}

void Shader::SetUniform3ui(const char* variableName, const unsigned int ui1, const unsigned int ui2, const unsigned int ui3)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform3ui(loc, ui1, ui2, ui3);
}

void Shader::SetUniform4ui(const char* variableName, const unsigned int ui1, const unsigned int ui2, const unsigned int ui3, const unsigned int ui4)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform4ui(loc, ui1, ui2, ui3, ui4);
}

/////////////////////////////////////////
///			UNIFORM FLOATS			  ///
/////////////////////////////////////////

void Shader::SetUniform1f(const char* variableName, const float f)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform1f(loc, f);
}

void Shader::SetUniform2f(const char* variableName, const float f1, const float f2)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform2f(loc, f1, f2);
}

void Shader::SetUniform3f(const char* variableName, const float f1, const float f2, const float f3)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform3f(loc, f1, f2, f3);
}

void Shader::SetUniform4f(const char* variableName, const float f1, const float f2, const float f3, const float f4)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniform4f(loc, f1, f2, f3, f4);
}

/////////////////////////////////////////
///			UNIFORM VECTORS 		  ///
/////////////////////////////////////////


void Shader::SetUniformVec4(const char* variableName, const glm::vec4& vec4)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");
	glUniform4fv(loc, 1, glm::value_ptr(vec4));

}

	/////////////////////////////////////////
	///			UNIFORM MATRICES	      ///
	/////////////////////////////////////////

void Shader::SetUniformMat4(const char* variableName, const glm::mat4& mat4)
{
	int loc = glGetUniformLocation(ID, variableName);
	if (loc == -1)
		Logger::LogError("Uniform " + std::string(variableName) + " NOT found");

	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4));
}