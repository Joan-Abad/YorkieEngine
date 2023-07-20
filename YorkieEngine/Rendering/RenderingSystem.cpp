#include "RenderingSystem.h"
#include "RenderObject.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

std::vector<RenderObject*> RenderingSystem::objectsToRender;

void RenderingSystem::AddObjectToRender(RenderObject* objectToRender)
{
	objectsToRender.push_back(objectToRender);
}

void RenderingSystem::RenderObjects(GLFWwindow* window)
{
	for (auto& renderObject : objectsToRender)
	{
		renderObject->Render();
	}
}

unsigned int RenderingSystem::CreateProgram()
{
	GLuint shaderProgram = glCreateProgram();

	return shaderProgram;
}

void RenderingSystem::AttachShaderToProgram(unsigned int Program, unsigned int Shader)
{
	glAttachShader(Program, Shader);

}

void RenderingSystem::UseProgram(unsigned int Program)
{
	glLinkProgram(Program);
	glUseProgram(Program);
}


