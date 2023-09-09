#pragma once
#include "Engine/YorkieEngine.h"
#include <string>

class YorkieAPI Texture
{
public: 
	std::string type;
	Texture() = default;
	Texture(const std::string& texturePath);
	void SetTextureID(unsigned int textureID);
	inline unsigned int GetTextureID() { return textureID; };
	void SetTexturePath(const std::string& texturePath);
	inline std::string& GetTexturePath() { return m_texturePath; };
private: 
	std::string m_texturePath;
	unsigned int textureID;
	int width; 
	int height; 
	int nrChannels;
};