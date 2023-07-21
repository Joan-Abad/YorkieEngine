#include "RenderObject.h"
#include "glad/glad.h"
#include "RenderingSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct Face
{
    unsigned int vIndex[3]; // Vertex indices for the face (assuming triangles)
};

int ParseVertexIndex(const std::string& faceIndexString)
{
    std::istringstream iss(faceIndexString);
    std::string vertexIndexStr;
    std::getline(iss, vertexIndexStr, '/');
    return std::stoi(vertexIndexStr);
}

RenderObject::RenderObject(const char* meshPath, Shader shader)
{
    std::ifstream objFile(meshPath);

    std::string line;
    while (std::getline(objFile, line))
    {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(0);
        }
        else if (prefix == "f")
        {
            std::istringstream issIndex(line.substr(2));
            Face face;
            std::string faceIndexString;
            while (issIndex >> faceIndexString)
            {
                indices.push_back(ParseVertexIndex(faceIndexString));
            }
            //faces.push_back(face);
        }
    }

    AttachShader(shader);
    CreateRenderObject();
}

RenderObject::RenderObject(const std::vector<float> vertices, Shader shader)
{
    this->vertices = vertices;
    AttachShader(shader);
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
    AttachShader(shader);
    CreateRenderObject();
}

RenderObject::~RenderObject()
{
    glDeleteProgram(shaderProgram);
}

void RenderObject::Render()
{
    ExecuteShader();
    glBindVertexArray(VAO);

    if (indices.size() > 0)
    {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
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

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (indices.size() > 0)
    {
        // Bind the EBO and copy the index data into it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }

    // Unbind the VAO
    glBindVertexArray(0);
    CreateShaderProgram();
}

void RenderObject::AttachShader(Shader shader)
{
    this->shader = shader;
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
