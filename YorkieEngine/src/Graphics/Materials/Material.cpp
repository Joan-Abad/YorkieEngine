#include "Graphics/Materials/Material.h"
#include "Graphics/Texture/Texture.h"
#include "Graphics/Shaders/Shader.h"
#include "glad/glad.h"
#include "glm.hpp"
#include <vector>

Material::Material(Shader* shader, Texture* albedo, Texture* specular, float shininess) : m_Shader(shader), m_Albedo(albedo), m_Specular(specular), m_Shininess(shininess)
{
	Diffuse = glm::vec3(0.1f);
	
    isUsingSpecular = m_Specular == nullptr ? false : true;
}

void Material::SetUVsCoordinate()
{
    if (m_Albedo)
    {
        std::vector<glm::vec2> TextureCoords = {
            // Front face
            glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left

            // Back face
           glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left

            // Right face
            glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left

            // Left face
           glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left

            // Top face
            glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left

            // Bottom face
            glm::vec2(0.0f, 0.0f), // Bottom-left
            glm::vec2(1.0f, 0.0f), // Bottom-right
            glm::vec2(1.0f, 1.0f), // Top-right
            glm::vec2(0.0f, 1.0f), // Top-left
        };

        //Set the data to the gpu
        glGenBuffers(1, &textureCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, textureCoordsVBO); // Texture coordinates buffer
        glBufferData(GL_ARRAY_BUFFER, TextureCoords.size() * 2 * sizeof(float), TextureCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glEnableVertexAttribArray(2);
    }
}
