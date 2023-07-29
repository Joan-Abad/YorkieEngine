#pragma once
#include "../YorkieEngine.h"

class GLFWwindow; 

struct Yorkie YorkiEngineAppInfo
{
	const char* title = "Yorki Engine";
	unsigned int screenWidth = 1920;
	unsigned int screenHeight = 1080;
};
class Yorkie YorkiEngineApp
{
public: 
	YorkiEngineApp();
	void Run();
private: 
	YorkiEngineAppInfo yorkiEngineAppInfo;
	
	void Update();
	void TerminateApplication();

	void InitializeGLFW();
	void InitializeGLAD();
	void InitializeImGUI();


protected:
	void CreateApplication();
	virtual void OnCreateApplicationCallback();
	virtual void OnPreDraw();
	virtual void OnPostDraw();
	virtual void OnTerimateApplication();
};

