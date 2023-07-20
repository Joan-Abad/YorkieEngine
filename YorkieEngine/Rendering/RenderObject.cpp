#include "RenderObject.h"
#include "glad/glad.h"
#include "RenderingSystem.h"

RenderObject::RenderObject(const std::vector<float> vertices)
{
    this->vertices = vertices;
    CreateRenderObject();
}

RenderObject::RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    CreateRenderObject();
}

RenderObject::RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices, Shader shader)
{
    this->vertices = vertices;
    this->indices = indices;
    CreateRenderObject();
    AttachShader(shader);
}

void RenderObject::Render()
{
    ExecuteShader();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void RenderObject::CreateRenderObject()
{
    RenderingSystem::AddObjectToRender(this);

    // Create a Vertex Array Object (VAO) and a Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO and copy the vertex data into it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Bind the EBO and copy the index data into it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);
}

void RenderObject::AttachShader(Shader shader)
{
    this->shader = shader;
}

void RenderObject::ExecuteShader()
{

    shaderProgram = glCreateProgram();


    glAttachShader(shaderProgram, shader.getVertexShaderID());


    glAttachShader(shaderProgram, shader.getFragmentShaderID());


    glLinkProgram(shaderProgram);

    glDeleteShader(shader.getVertexShaderID());
    glDeleteShader(shader.getFragmentShaderID());
    glUseProgram(shaderProgram);
}
