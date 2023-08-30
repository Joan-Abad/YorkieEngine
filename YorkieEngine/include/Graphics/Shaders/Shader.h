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

    /////////////////////////////////////////
    ///			UNIFORM INTEGERS		  ///
    /////////////////////////////////////////

    void SetUniform1i(const char* variableName, const int i);
    void SetUniform2i(const char* variableName, const int i1, const int i2);
    void SetUniform3i(const char* variableName, const int i1, const int i2, const int i3);
    void SetUniform4i(const char* variableName, const int i1, const int i2, const int i3, const int i4);

    /////////////////////////////////////////
    ///		UNIFORM UNSIGNED INTEGERS	  ///
    /////////////////////////////////////////

    void SetUniform1ui(const char* variableName, const unsigned int ui);
    void SetUniform2ui(const char* variableName, const unsigned int ui1, const unsigned int ui2);
    void SetUniform3ui(const char* variableName, const unsigned int ui1, const unsigned int ui2, const unsigned int ui3);
    void SetUniform4ui(const char* variableName, const unsigned int ui1, const unsigned int ui2, const unsigned int ui3, const unsigned int ui4);

    /////////////////////////////////////////
    ///			UNIFORM FLOATS			  ///
    /////////////////////////////////////////

    void SetUniform1f(const char* variableName, const float f);
    void SetUniform2f(const char* variableName, const float f1, const float f2);
    void SetUniform3f(const char* variableName, const float f1, const float f2, const float f3);
    void SetUniform4f(const char* variableName, const float f1, const float f2, const float f3, const float f4);

    /////////////////////////////////////////
    ///			UNIFORM VECTORS 		  ///
    /////////////////////////////////////////

    void SetUniformVec4(const char* variableName, const glm::vec4& vec4);

    /////////////////////////////////////////
    ///			UNIFORM MATRICES	      ///
    /////////////////////////////////////////

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