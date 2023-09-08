#pragma once
#include "Engine/YorkieEngine.h"
#include <string>
#include "glm.hpp"

class Shader; 
class Texture; 

class YorkieAPI Material
{
	friend class Mesh;
public: 
	Material() = default;
	Material(Shader* shader, Texture* albedo = nullptr, Texture* specular = nullptr, float shininess = 32.f);

	inline float GetShininess() const { return m_Shininess; };
	inline Shader& GetShader() const { return *m_Shader; };
	inline bool IsUsingSpecularTexture() const { return isUsingSpecular; };
	inline Texture* GetAlbedoTexture() const { return m_Albedo; };
	inline Texture* GetSpecularTexture() const { return m_Specular; };
private: 
	//How much the object shiness to light when affected by specular
	float m_Shininess;
	//Main color 
	Texture* m_Albedo;
	//Specular texture
	Texture* m_Specular;
	//Diffuse color scalar, overall light. If there is no light hitting it, this value will multiply the pixel color
	glm::vec3 Diffuse;
	//Shader used to render this material
	Shader* m_Shader;
	
	unsigned textureCoordsVBO;

	bool isUsingSpecular;
};