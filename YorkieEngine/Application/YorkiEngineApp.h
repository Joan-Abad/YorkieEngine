#pragma once
#include "../YorkieEngine.h"
#include "../Modules/ShaderModule.h"

class GLFWwindow; 

struct Yorkie YorkiEngineAppInfo
{
	const char* title = "Yorki Engine";
	unsigned int screenWidth = 2560;
	unsigned int screenHeight = 1440;
};
class Yorkie YorkiEngineApp
{
public: 
	YorkiEngineApp();
	void Run();
	static double GetTime();

private: 
	bool bIsRunning;
	YorkiEngineAppInfo yorkiEngineAppInfo;
	
	void Update();
	void TerminateApplication();

	void InitializeGLFW();
	void InitializeGLAD();
	void InitializeImGUI();
	void InitializeEngineModules();

protected:
	void CreateApplication();
	void InitializeWindows();
	virtual void OnCreateApplicationCallback();
	virtual void OnPreDraw();
	virtual void OnPostDraw();
	virtual void OnTerimateApplication();
};

