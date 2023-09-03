#include "Components/TextureComponent.h"
#include "glad/glad.h"
#include "Logging/Logger.h"

TextureComponent::TextureComponent(const std::string& imagePath)
{
	this->imagePath = imagePath;

    // load and create a texture 
    // -------------------------
    // texture 1
    // ---------
    
}

void TextureComponent::SetTextureData()
{
    std::vector<glm::vec2> TextureCoords = {
        // Front face
        glm::vec2(0.0f, 0.0f), // Bottom-left
        glm::vec2(1.0f, 0.0f), // Bottom-right
        glm::vec2(1.0f, 1.0f), // Top-right
        glm::vec2(0.0f, 1.0f), // Top-left

        // Back face
        glm::vec2(1.0f, 0.0f), // Bottom-left
        glm::vec2(0.0f, 0.0f), // Bottom-right
        glm::vec2(0.0f, 1.0f), // Top-right
        glm::vec2(1.0f, 1.0f), // Top-left

        // Right face
        glm::vec2(0.0f, 0.0f), // Bottom-left
        glm::vec2(1.0f, 0.0f), // Bottom-right
        glm::vec2(1.0f, 1.0f), // Top-right
        glm::vec2(0.0f, 1.0f), // Top-left

        // Left face
        glm::vec2(1.0f, 0.0f), // Bottom-left
        glm::vec2(0.0f, 0.0f), // Bottom-right
        glm::vec2(0.0f, 1.0f), // Top-right
        glm::vec2(1.0f, 1.0f), // Top-left

        // Top face
        glm::vec2(0.0f, 1.0f), // Bottom-left
        glm::vec2(1.0f, 1.0f), // Bottom-right
        glm::vec2(1.0f, 0.0f), // Top-right
        glm::vec2(0.0f, 0.0f), // Top-left

        // Bottom face
        glm::vec2(0.0f, 0.0f), // Bottom-left
        glm::vec2(1.0f, 0.0f), // Bottom-right
        glm::vec2(1.0f, 1.0f), // Top-right
        glm::vec2(0.0f, 1.0f)  // Top-left
    };

    //Set the data to the gpu
    glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Texture coordinates buffer
    glBufferData(GL_ARRAY_BUFFER, TextureCoords.size() * 2 *sizeof(float), TextureCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(2);
}

void TextureComponent::AttachShader(Shader& shader)
{
    this->shader = &shader;
}
