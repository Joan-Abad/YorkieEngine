#include "Shader.h"
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

void Shader::ExecuteShader()
{
}
