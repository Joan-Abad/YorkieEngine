#pragma once
#include <vector>
#include <memory>


class RenderingSystem
{
public:
	static void AddObjectToRender(class RenderObject objectToRender);
	static void RenderObjects(class GLFWwindow* window);

private:
	static std::vector<class RenderObject> objectsToRender;

	//static void Render
};

