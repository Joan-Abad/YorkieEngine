#pragma once

#include "GLFW/glfw3.h"
#include "Engine/YorkieEngine.h"
#include <string>
#include "glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
//Contains fragment and vertex shader
class YorkieAPI Shader
{
public:
    Shader() = default;
    Shader(const char* shaderPath);
    void ParseShader(const std::string& path);
    void Bind();
    void Unbind();

    void SetUniformVec4(const char* variableName, const glm::vec4& vec4);
    void SetUniformMat4(const char* variableName, const glm::mat4& mat4);

    inline unsigned int getVertexShaderID() { return vertexShaderID; };
    inline unsigned int getFragmentShaderID() { return fragmentShaderID; };
    inline unsigned int getProgramID() { return ID; };
private:
    void CheckShaderCompilationStatus(GLuint shader);

    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int ID;
    ShaderProgramSource shaderProgramSource;
};