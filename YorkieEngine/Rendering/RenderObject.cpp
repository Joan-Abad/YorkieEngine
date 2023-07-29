#include "RenderObject.h"
#include "glad/glad.h"
#include "RenderingSystem.h"
#include <sstream>
#include <vector>

RenderObject::RenderObject()
{

}

RenderObject::~RenderObject()
{
    glDeleteProgram(shaderProgram);
}

void RenderObject::Render()
{
    glad_glUseProgram(shaderProgram);

    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    vao.Unbind();

}

void RenderObject::AttachShader(Shader shader)
{
    this->shader = shader;
    CreateShaderProgram();
}

void RenderObject::AddVBOBuffer(VBO& vbo)
{
    vbos.push_back(&vbo);
}

void RenderObject::CreateShaderProgram()
{
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, shader.getVertexShaderID());
    glAttachShader(shaderProgram, shader.getFragmentShaderID());
    glLinkProgram(shaderProgram);
    glDeleteShader(shader.getVertexShaderID());
    glDeleteShader(shader.getFragmentShaderID());
}

void RenderObject::ExecuteShader()
{
    glUseProgram(shaderProgram);
}
