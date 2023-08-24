#include "Input/Input.h"

Input::Input(Window& window)
{
	this->window = &window;
}

bool Input::IsKeyPressed(EKeyboardKeys keyboardKeys)
{
	return glfwGetKey(window->GetWindow(), keyboardKeys) == GLFW_PRESS;
}
