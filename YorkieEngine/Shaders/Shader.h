#pragma once

#include "GLFW/glfw3.h"
#include "../YorkieEngine.h"
#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
//Conains fragment and vertex shader
class YENGINE Shader
{
public:
    Shader() = default;
    Shader(const char* shaderPath);

private:
    void CheckShaderCompilationStatus(GLuint shader);

    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    ShaderProgramSource shaderProgramSource;

    void ParseShader(const std::string& path);

public:
    inline unsigned int getVertexShaderID() { return vertexShaderID; };
    inline unsigned int getFragmentShaderID() { return fragmentShaderID; };
};