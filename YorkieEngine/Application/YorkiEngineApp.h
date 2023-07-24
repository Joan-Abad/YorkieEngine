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
	YorkiEngineAppInfo yorkiEngineAppInfo;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
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

public: 

};

