#pragma once
#include "../YorkieEngine.h"

class GLFWwindow; 

struct YENGINE YorkiEngineAppInfo
{
	const char* title = "Yorki Engine";
	unsigned int screenWidth = 1920;
	unsigned int screenHeight = 1080;
};
class YENGINE YorkiEngineApp
{
public: 
	YorkiEngineApp();
	void Run();
private: 
	GLFWwindow* window;
	YorkiEngineAppInfo yorkiEngineAppInfo;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	void CreateApplication();
	void Update();
	void TerminateApplication();
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

protected:
	virtual void OnCreateApplication();
	virtual void OnPreDraw();
	virtual void OnPostDraw();
	virtual void OnTerimateApplication();

};

