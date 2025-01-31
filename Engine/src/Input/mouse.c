#include "Input/mouse.h"

bool mouse_scrollUp = false;
bool mouse_scrollDown = false;

int mouse_isButtonPressed(window_s* window, int button)
{
    return (glfwGetMouseButton(window->window, button)) == GLFW_PRESS;
}

int mouse_isButtonReleased(window_s* window, int button)
{
    return (glfwGetMouseButton(window->window, button)) == GLFW_RELEASE;
}

void mouse_getMousePosition(window_s* window, vec2_s* position)
{
    double x, y;
    glfwGetCursorPos(window->window, &x, &y);
    position->x = x;
    position->y = y;
}

void callback_scroll(GLFWwindow* window, double x, double y)
{
    if (y == 1 && mouse_scrollUp == false) mouse_scrollUp = true;
    else mouse_scrollUp = false;
    if (y == -1 && mouse_scrollDown == false) mouse_scrollDown = true;
    else mouse_scrollDown = false;
}
