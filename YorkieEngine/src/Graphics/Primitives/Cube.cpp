#include "Graphics/Primitives/Cube.h"
#include "glad/glad.h"

Cube::Cube(Viewport* viewport) : GameEntity(viewport)
{
    shader = nullptr;
    model = glm::mat4(1.0f);
    /*
    std::vector<Vertex> CubeVertecies = {
        // Front face
        Vertex(glm::vec3(-0.5f, -0.5f,  0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f, -0.5f,  0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f,  0.5f,  0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f,  0.5f,  0.5f)), // Top-left

        // Back face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f,  0.5f, -0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f,  0.5f, -0.5f)), // Top-left

        // Right face
        Vertex(glm::vec3(0.5f, -0.5f,  0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f,  0.5f, -0.5f)), // Top-right
        Vertex(glm::vec3(0.5f,  0.5f,  0.5f)), // Top-left

        // Left face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)), // Bottom-left
        Vertex(glm::vec3(-0.5f, -0.5f,  0.5f)), // Bottom-right
        Vertex(glm::vec3(-0.5f,  0.5f,  0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f,  0.5f, -0.5f)), // Top-left

        // Top face
        Vertex(glm::vec3(-0.5f,  0.5f,  0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f,  0.5f,  0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f,  0.5f, -0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f,  0.5f, -0.5f)), // Top-left

        // Bottom face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f, -0.5f,  0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f, -0.5f,  0.5f))  // Top-left
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
    
    this->indices = indices;

    SetupMesh();
    */
}