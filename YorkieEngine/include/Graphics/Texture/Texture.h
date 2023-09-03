#pragma once
#include "Engine/YorkieEngine.h"
#include <string>

class YorkieAPI Texture
{
public: 
	Texture(const std::string& texturePath);
	inline unsigned int GetTextureID() { return textureID; };
private: 
	std::string m_texturePath;
	unsigned int textureID;
	int width; 
	int height; 
	int nrChannels;
};