#include "VBO.h"
#include "GLFW/glfw3.h"

VBO::VBO(std::vector<float>& data, int layout, unsigned int VAO, unsigned int &layoutIndex)
{

    if (VAO)
        glBindVertexArray(VAO);

    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    if(layoutIndex == 0)
        glVertexAttribPointer(layoutIndex, layout, GL_FLOAT, GL_FALSE, layout * sizeof(float), (void*)0);
    if (layoutIndex == 1)
        glVertexAttribPointer(0, layout, GL_FLOAT, GL_FALSE, layout * sizeof(float), (void*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(layoutIndex);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    layoutIndex++;
}   

VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}
