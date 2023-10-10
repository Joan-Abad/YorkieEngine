#include "Graphics/Texture/Texture.h"
#include "glad/glad.h"
#include "Logging/Logger.h"
#include "stb_image.h"


Texture::Texture(const std::string& texturePath)
{
	this->m_texturePath = texturePath;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(m_texturePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 2)
            format = GL_ALPHA;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        Logger::LogInfo(m_texturePath + " loaded correctly");
    }
    else
    {
        Logger::LogError("Failed to load texture");
    }


    stbi_image_free(data);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Texture coordinates buffer
}

void Texture::SetTextureID(unsigned int textureID)
{
    this->textureID = textureID;
}

void Texture::SetTexturePath(const std::string& texturePath)
{
    this->m_texturePath = texturePath;
}
