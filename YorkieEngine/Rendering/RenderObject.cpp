#include "RenderObject.h"
#include "glad/glad.h"

RenderObject::RenderObject(const std::vector<float> vertices)
{
    this->vertices = vertices;
    Render();
}

RenderObject::RenderObject(const std::vector<float> vertices, const std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    Render();
}

void RenderObject::Render()
{
    // Create Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create Vertex Buffer Object (VBO) for vertex positions
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create Element Buffer Object (EBO) for vertex indices
    unsigned int EBO;

    //Use element buffer object
    if (indices.size() > 0)
    {

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
    }
    //Don't use it 
    else
    {

    }

    shaderProgram = glCreateProgram();

    
    glAttachShader(shaderProgram, vertexShader.getShaderID());
    
    
    glAttachShader(shaderProgram, fragmentShader.getShaderID());
    

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader.getShaderID());
    glDeleteShader(fragmentShader.getShaderID());
    glUseProgram(shaderProgram);

    
}

void RenderObject::AttachVertexShader(Shader vertexShader)
{
    this->vertexShader = vertexShader;
}

void RenderObject::AttachFragmentShader(Shader fragmentShader)
{
    this->fragmentShader = fragmentShader;
}
