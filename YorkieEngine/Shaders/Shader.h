#pragma once

#include "GLFW/glfw3.h"
#include "../YorkieEngine.h"
#include <string>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
//Contains fragment and vertex shader
class Yorkie Shader
{
public:
    Shader() = default;
    Shader(const char* shaderPath);
    void ParseShader(const std::string& path);
    void ExecuteShader();
    void StopShader();

private:
    void CheckShaderCompilationStatus(GLuint shader);

    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int ID;
    ShaderProgramSource shaderProgramSource;

public:
    inline unsigned int getVertexShaderID() { return vertexShaderID; };
    inline unsigned int getFragmentShaderID() { return fragmentShaderID; };
    inline unsigned int getProgramID() { return ID; };
};