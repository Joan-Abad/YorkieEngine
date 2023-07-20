#pragma once
#include <vector>
#include <memory>
#include "../YorkieEngine.h"
#include <string>

class YENGINE RenderingSystem
{
public:
	static void AddObjectToRender(class RenderObject* objectToRender);
	static void RenderObjects(class GLFWwindow* window);
	static unsigned int CreateProgram();
	static void AttachShaderToProgram(unsigned int Program, unsigned int Shader);
	static void UseProgram(unsigned int Program);
private:
	static std::vector<class RenderObject*> objectsToRender;

	//static void Render
};

