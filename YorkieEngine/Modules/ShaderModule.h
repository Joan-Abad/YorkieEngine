#pragma once
#include "../Shaders/Shader.h"
#include "../YorkieEngine.h"

class Yorkie ShaderModule
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

