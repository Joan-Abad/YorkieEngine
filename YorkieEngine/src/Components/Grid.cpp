#include "Editor/Grid.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>

//Grid code: https://stackoverflow.com/questions/58494179/how-to-create-a-grid-in-opengl-and-drawing-it-with-lines

Grid::Grid() : quadSize(100), slices(50)
{
    float positionOffset = quadSize / 2;
    float x;
    float y;
    float z;
    for (int j = 0; j <= slices; ++j) {
           
        for (int i = 0; i <= slices; ++i) {
            x = ((float)i / (float)slices) * quadSize - positionOffset;
            y = 0;
            z = ((float)j / (float)slices) * quadSize - positionOffset;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }
    std::cout << "X: " << x << "Y: " << y << "Z: " << z << std::endl;

    for (int j = 0; j < slices; ++j) {
        for (int i = 0; i < slices; ++i) {

            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

        }
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    length = (GLuint)indices.size() * 4;

    shader = new Shader("res/shaders/grid.shader");

}

void Grid::DrawGrid()
{
    shader->Bind();

    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(vao);

    glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);

    glDisable(GL_DEPTH_TEST);

    shader->Unbind();
}
