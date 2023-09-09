#pragma once
#include "YorkieEngine.h"
#include "Modules/ShaderModule.h"
#include "Window/Window.h"

class GLFWwindow; 

struct YorkieAPI YorkieEngineAppConfig
{
	WindowProperties levelEditorWindowProps;
};

class YorkieAPI YorkieEngineApp
{
public: 
	YorkieEngineApp();
	//Call to run the engine
	void Run();
	//Call to shutdown the engine
	void Shutdown();
	//Returns the gametime since the start of the game
	static double GetGameTime();
	//Returns the delta time 
	static double GetDeltaTime();
protected:
	void CreateApplication();
	//This function needs to be called after glfw initialization and before initializing glad
	void CreateEngineViewport();
	//Triggers the callback for any sandbos of YorkieEngineApp
	void InitGame();
	//Calls Init function on all windows
	void InitializeWindows();
	virtual void OnCreateApplicationCallback();
	virtual void OnUpdate(float deltaTime);
	virtual void OnPostUpdate();
	virtual void OnTerimateApplication();

private:
	bool bIsRunning;
	//Time tracker that holds previous frame time for delta time
	double previousTimeTracker;
	//Time between frames
	static double deltaTime;
	//Tracks to see if it has already passed one second
	double fpsTimeTracker;
	//Frames per second
	unsigned int FPS;
	//Configuration of Yorkie Engine
	YorkieEngineAppConfig yorkiEngineAppConfig;

	void Update();
	void TerminateApplication();
	void SetDeltaTime();

	//Initialize Dependencies
	void InitializeGLFW();
	void InitializeGLAD();
	void InitializeImGUI();
	void InitializeEngineModules();
};

