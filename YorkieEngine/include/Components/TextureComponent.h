#include "Components/BaseComponent.h"
#include "Engine/YorkieEngine.h"
#include "Graphics/Shaders/Shader.h"
#include <iostream>
#include <string>
#include <vector>

class YorkieAPI TextureComponent
{
public: 
	TextureComponent(const std::string& imagePath);
	void SetTextureData();
	void AttachShader(Shader& shader);
private:
	int width, height, nrChannels;
	unsigned int textureID;
	unsigned int VBO;
	std::string imagePath;
	Shader* shader;
};