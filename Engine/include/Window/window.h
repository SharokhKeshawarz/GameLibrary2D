#ifndef WINDOW_H
#define WINDOW_H

#include "core/main.h"
#include "core/vec.h"

typedef struct window_s
{
    vec2_s size;    
    vec2_s posision;
    char* title;
    GLFWwindow* window;
} window_s;

window_s* window_create(int width, int height, char* title, bool resizable);
vec2_s window_getSize(window_s* window);
int window_getWidth(window_s* window);
int window_getHeight(window_s* window);
vec2_s window_getPosition(window_s* window);
int window_getPositionX(window_s* window);
int window_getPositionY(window_s* window);
char *window_getTitle(window_s* window);
bool window_shouldClose(window_s* window);
void window_setFps(unsigned int target_fps);
void window_showFps();
double window_getDeltaTime();
void window_clear(float r, float g, float b, float a);
void window_display(window_s* window, int quit_key);
void window_quit(window_s* window, int key);
void window_destroy(window_s* window);

#endif 
