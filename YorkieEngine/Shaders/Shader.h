#pragma once

#include "GLFW/glfw3.h"
#include "../YorkieEngine.h"

class YENGINE Shader
{
public:
    Shader() = default;
    Shader(const char* shaderSource, GLenum type);

private:
    void CheckShaderCompilationStatus(GLuint shader);

    const char* shaderSource;
    unsigned int shaderID;

public:
    inline unsigned int getShaderID() { return shaderID; };
};