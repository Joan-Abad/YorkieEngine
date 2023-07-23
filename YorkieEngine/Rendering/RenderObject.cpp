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
// Function to print the program info log
void PrintProgramInfoLog(GLuint program) {
    GLint logLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        char* logBuffer = new char[logLength];
        glGetProgramInfoLog(program, logLength, nullptr, logBuffer);
        std::cout << "Program Info Log:\n" << logBuffer << std::endl;
        delete[] logBuffer;
    }
}
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
    /*
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
    */
    AttachShader(shader);
}

RenderObject::RenderObject(const std::vector<float> vertices, Shader shader)
{
    RenderingSystem::AddObjectToRender(this);
   // buffer.AddBufferData(vertices);
    AttachShader(shader);
    //CreateRenderObject();

}

RenderObject::RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    buffer.AddBufferData(vertices);
    buffer.AddBufferData(indices);
}

RenderObject::RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices, Shader shader)
{
    buffer.AddBufferData(vertices);
    buffer.AddBufferData(indices);
    AttachShader(shader);
}

RenderObject::~RenderObject()
{
    glDeleteProgram(shaderProgram);
}

void RenderObject::Render()
{
    /*float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
    ExecuteShader();
    glBindVertexArray(buffer.GetVAO());
    /*
    if (indices.size() > 0)
    {
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    */
    //else
    //{
        glDrawArrays(GL_TRIANGLES, 0, 3);
    //}
    glBindVertexArray(0);

}

void RenderObject::AttachShader(Shader shader)
{
    this->shader = shader;
    CreateShaderProgram();
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
