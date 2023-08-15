#include "ShaderModule.h"
#include "../Logging/Public/Logger.h"

ShaderModule* ShaderModule::instance = nullptr;
Shader* ShaderModule::defaultShader = nullptr;


ShaderModule::ShaderModule()
{
	defaultShader = new Shader("res/shaders/default.shader");

	if (!defaultShader)
		Logger::LogError("DEFAULT SHADER COULD NOT BE CREATED");
	else
		Logger::LogInfo("Default Shader loaded.");
}

Shader* ShaderModule::GetDefaultShader()
{
	return defaultShader;
}
