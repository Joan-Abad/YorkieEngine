#include "Shader.h"
#include <iostream>
#include <vector>

Shader::Shader(const char* shaderSource, GLenum type) : shaderSource(shaderSource)
{
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &shaderSource, nullptr);
	glCompileShader(shaderID);
    CheckShaderCompilationStatus(shaderID);

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
