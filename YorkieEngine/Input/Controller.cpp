#include "Controller.h"

Controller::Controller(Window& window)
{
    this->window = &window;
}

bool Controller::IsKeyPressed(EKeyboardKeys KeyboardKey)
{
    return glfwGetKey(window->GetWindow(), KeyboardKey) == GLFW_PRESS;
}


