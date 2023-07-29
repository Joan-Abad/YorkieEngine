#include "../Public/WindowManager.h"

std::vector<Window*> WindowManager::windows;
 Window* WindowManager::activeWindow;

//void WindowManager::CreateWindow(int width, int height, const char* title, WindowMode windowMode)
//{
//	Window* window = new Window(width, height, title, windowMode);
//	windows.push_back(window);
//
//	if(!activeWindow)
//		SetActiveWindow(*window);
//}

void WindowManager::SetActiveWindow(Window& window)
{
	activeWindow = &window;

	// Make the window's context current
	glfwMakeContextCurrent(window.GetWindow());
	//int width, height;
	//glfwGetFramebufferSize(activeWindow->window, &width, &height);
	//glViewport(0, 0, width, height);

	
}
Window& WindowManager::GetActiveWindow()
{
	// TODO: insert return statement here
	return *activeWindow;
}
void WindowManager::DrawWindows()
{
	for (auto& window : windows)
	{
		window->Draw();
	}
}
