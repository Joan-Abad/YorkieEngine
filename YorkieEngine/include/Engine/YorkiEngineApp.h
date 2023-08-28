#pragma once
#include "YorkieEngine.h"
#include "Modules/ShaderModule.h"

class GLFWwindow; 

struct YorkieAPI YorkiEngineAppInfo
{
	const char* title = "Yorki Engine";
	unsigned int screenWidth = 2560;
	unsigned int screenHeight = 1440;
};
class YorkieAPI YorkiEngineApp
{
public: 
	YorkiEngineApp();
	void Run();
	static double GetTime();
	
private: 
	bool bIsRunning;
	double previousTime;
	double fpsTimeTracker;
	unsigned int FPS;
	YorkiEngineAppInfo yorkiEngineAppInfo;

	void Update();
	void TerminateApplication();
	double SetDeltaTime();

	void InitializeGLFW();
	void InitializeGLAD();
	void InitializeImGUI();
	void InitializeEngineModules();

protected:
	void CreateApplication();
	void InitializeWindows();
	virtual void OnCreateApplicationCallback();
	virtual void OnUpdate();
	virtual void OnPostUpdate();
	virtual void OnTerimateApplication();
};

