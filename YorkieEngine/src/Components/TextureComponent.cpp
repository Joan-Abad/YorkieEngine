#include "Components/TextureComponent.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "Logging/Logger.h"

TextureComponent::TextureComponent(const std::string& imagePath)
{
	this->imagePath = imagePath;
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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(1);

    // load and create a texture 
    // -------------------------
    // texture 1
    // ---------
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }   

    Logger::LogInfo(imagePath + " loaded correctly");

    stbi_image_free(data);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Texture coordinates buffer

}

void TextureComponent::AttachShader(Shader& shader)
{
    this->shader = &shader;
}
