#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Engine/YorkieEngine.h"

enum class YorkieAPI WindowMode
{
	Windowed,
	FullScreen,
	Borderless
};

struct YorkieAPI WindowProperties
{
	WindowProperties(int width = 3840, int height = 2160, WindowMode windowMode = WindowMode::Windowed) 
		: m_Width(width), m_Height(height), m_WindowMode(windowMode)
	{

	}

	int m_Width, m_Height;
	WindowMode m_WindowMode;
	const char* m_Title = "Yorkie Engine";
};

class YorkieAPI  Window
{
	friend class WindowManager;
	friend class GameEntity;
public:
	Window() = default;
	Window(const WindowProperties windowProperties);
protected:
	bool bDrawWindow;
	GLFWwindow* window;

	virtual void Init();
	virtual void Update(float deltaTime);

public:
	inline GLFWwindow* GetWindow() { return window; };
	int GetWindowWidth();
	int GetWindowHeight();
	float GetAspectRatio();
	
};

