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

private: 
	GLFWwindow* window;
	YorkiEngineAppInfo yorkiEngineAppInfo;

public:
	void CreateApplication();
	void Update();
	void TerminateApplication();

};

