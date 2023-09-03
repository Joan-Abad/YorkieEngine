#include "Graphics/Primitives/Cube.h"
#include "glad/glad.h"
#include "Components/MeshComponent.h"

Cube::Cube() : GameEntity()
{

}

void Cube::OnConstruct()
{
    std::vector<Vertex> cubeVertices = {
        // Front face
        Vertex(glm::vec3(-0.5f, -0.5f,  0.5f)), // Bottom-left
        Vertex(glm::vec3(0.5f, -0.5f,  0.5f)), // Bottom-right
        Vertex(glm::vec3(0.5f,  0.5f,  0.5f)), // Top-right
        Vertex(glm::vec3(-0.5f,  0.5f,  0.5f)), // Top-left

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

    std::vector<unsigned int> cubeIndices = {
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

}
