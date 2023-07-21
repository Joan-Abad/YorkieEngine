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
private:
	static std::vector<class RenderObject*> objectsToRender;

	//static void Render
};

