#pragma once
#include "Window.h"
#include <vector>
#include "../../YorkieEngine.h"

class Yorkie WindowManager
{
	friend class Window;
public:
	template <typename WindowType = Window>
	static Window* CreateWindow(int width = 800, int height = 600, const char* title = "YorkiEngine", WindowMode windowMode = WindowMode::Windowed)
	{
		Window* window = new WindowType(width, height, title, windowMode);
		windows.push_back(window);

		if (!activeWindow)
			SetActiveWindow(*window);

		return window;
	}

	static void DrawWindows();

	static Window& GetActiveWindow();
private:
	static std::vector<Window*> windows;
	static Window* activeWindow;

	static void SetActiveWindow(Window& window);
	
};

