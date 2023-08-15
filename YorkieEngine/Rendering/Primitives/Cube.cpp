#include "Cube.h"
#include "glad/glad.h"

Cube::Cube()
{
    shader = nullptr;
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    std::vector<glm::vec3> CubeVertecies = {
        // Front face
        glm::vec3(-0.5f, -0.5f,  0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f,  0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f,  0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f,  0.5f), // Top-left

        // Back face
        glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f, -0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left

        // Right face
        glm::vec3(0.5f, -0.5f,  0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f, -0.5f), // Top-right
        glm::vec3(0.5f,  0.5f,  0.5f), // Top-left

        // Left face
        glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-left
        glm::vec3(-0.5f, -0.5f,  0.5f), // Bottom-right
        glm::vec3(-0.5f,  0.5f,  0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left

        // Top face
        glm::vec3(-0.5f,  0.5f,  0.5f), // Bottom-left
        glm::vec3(0.5f,  0.5f,  0.5f), // Bottom-right
        glm::vec3(0.5f,  0.5f, -0.5f), // Top-right
        glm::vec3(-0.5f,  0.5f, -0.5f), // Top-left

        // Bottom face
        glm::vec3(-0.5f, -0.5f, -0.5f), // Bottom-left
        glm::vec3(0.5f, -0.5f, -0.5f), // Bottom-right
        glm::vec3(0.5f, -0.5f,  0.5f), // Top-right
        glm::vec3(-0.5f, -0.5f,  0.5f)  // Top-left
    };
    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Right face
        8, 9, 10,
        10, 11, 8,

        // Left face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20
    };
    for (int i = 0; i < CubeVertecies.size(); i++)
    {
        Vertex vertex;
        vertex.Position = CubeVertecies[i];
        vertices.push_back(vertex);
    }
    this->indices = indices;

    SetupMesh();
}