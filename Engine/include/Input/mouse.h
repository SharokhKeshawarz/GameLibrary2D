#ifndef MOUSE_H
#define MOUSE_H

#include "core/main.h"
#include "Window/window.h"

extern bool mouse_scrollUp;
extern bool mouse_scrollDown;

int mouse_isButtonPressed(window_s* window, int button);
int mouse_isButtonReleased(window_s* window, int button);
void mouse_getMousePosition(window_s* window, vec2_s* position);
void callback_scroll(GLFWwindow* window, double x, double y);

#pragma region MOUSE_BUTTONS

#define MOUSE_BUTTON_1 GLFW_MOUSE_BUTTON_1
#define MOUSE_BUTTON_2 GLFW_MOUSE_BUTTON_2
#define MOUSE_BUTTON_3 GLFW_MOUSE_BUTTON_3
#define MOUSE_BUTTON_4 GLFW_MOUSE_BUTTON_4
#define MOUSE_BUTTON_5 GLFW_MOUSE_BUTTON_5
#define MOUSE_BUTTON_6 GLFW_MOUSE_BUTTON_6
#define MOUSE_BUTTON_7 GLFW_MOUSE_BUTTON_7
#define MOUSE_BUTTON_8 GLFW_MOUSE_BUTTON_8
#define MOUSE_BUTTON_LAST GLFW_MOUSE_BUTTON_LAST
#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT

#pragma endregion /* MOUSE_BUTTONS */

#endif
