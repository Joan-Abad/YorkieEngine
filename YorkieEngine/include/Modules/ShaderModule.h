#pragma once
#include "Graphics/Shaders/Shader.h"
#include "Engine/YorkieEngine.h"

class YorkieAPI ShaderModule
{
public:
	ShaderModule();

	static ShaderModule* GetShaderModule()
	{
		if (!instance)
			instance = new ShaderModule();
		else
			return instance;

		return instance;
	}
	
	Shader* GetDefaultShader();
private:
	static ShaderModule* instance;

	static Shader* defaultShader;
};

