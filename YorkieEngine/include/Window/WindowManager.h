#pragma once
#include "Window.h"
#include <vector>
#include "Engine/YorkieEngine.h"

class YorkieAPI WindowManager
{
	friend class Window;
public:
	template <typename WindowType = Window, typename... Args>
	static WindowType* CreateWindow(Args&&... args)
	{
		WindowType* window = new WindowType(std::forward<Args>(args)...);
		windows.push_back(window);

		if (!activeWindow)
			SetActiveWindow(*window);

		return window;
	}

	static void DrawWindows(float frameTime);

	template<typename T>
	static T& GetActiveWindow()
	{
		return dynamic_cast<T&>(*activeWindow);
	}
	static Window& GetWindow(int index);

	static void InitWindows();
private:
	static std::vector<Window*> windows;
	static Window* activeWindow;

	static void SetActiveWindow(Window& window);
	
};

