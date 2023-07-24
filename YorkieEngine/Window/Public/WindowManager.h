#pragma once
#include "Window.h"
#include <vector>

class WindowManager
{
	friend class Window;
public:
	template <typename WindowType = Window>
	static void CreateWindow(int width = 800, int height = 600, const char* title = "YorkiEngine", WindowMode windowMode = WindowMode::Windowed)
	{
		Window* window = new WindowType(width, height, title, windowMode);
		windows.push_back(window);

		if (!activeWindow)
			SetActiveWindow(*window);
	}

	static void DrawWindows();

	inline Window& GetActiveWindow() { return *activeWindow; }
private:
	static std::vector<Window*> windows;
	static Window* activeWindow;

	static void SetActiveWindow(Window& window);
	
};

