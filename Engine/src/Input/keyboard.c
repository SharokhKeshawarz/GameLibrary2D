#include "Input/keyboard.h"

int keyboard_isKeyPressed(window_s* window, int key)
{
    return glfwGetKey(window->window, key) == GLFW_PRESS;
}

int keyboard_isKeyReleased(window_s* window, int key)
{
    return glfwGetKey(window->window, key) == GLFW_RELEASE;
}

void keyboard_handleSingleKey(window_s* window, int key, float debounceTime, void (*call_back)(va_list), ...)
{
    static float lastInputTime[GLFW_KEY_LAST] = {0};  // Store last input time for each key
    float currentTime = (float)glfwGetTime();

    if (keyboard_isKeyPressed(window, key)) {
        if (currentTime - lastInputTime[key] >= debounceTime) {
            va_list args;
            va_start(args, call_back);
            call_back(args);
            va_end(args);
            lastInputTime[key] = currentTime;  // Update last input time for this key
        }
    }
}

void keyboard_handleMultipleKeys(window_s* window, int* keys, float* debounceTimes, void (**call_backs)(int, va_list), int num_keys, ...)
{
    static float lastInputTime[GLFW_KEY_LAST] = {0};
    float currentTime = (float)glfwGetTime();

    for (int i = 0; i < num_keys; i++) {
        int key = keys[i];
        float debounceTime = debounceTimes[i];
        void (*call_back)(int, va_list) = call_backs[i];

        if (keyboard_isKeyPressed(window, key)) {
            if (currentTime - lastInputTime[key] >= debounceTime) {
                va_list args;
                va_start(args, num_keys);
                call_back(key, args);
                va_end(args);
                lastInputTime[key] = currentTime;
            }
        }
    }
}

void keyboard_handleKeyCombinaison(window_s* window, int** key_combinations, float* debounceTimes, void (**call_backs)(va_list), int num_combinations, ...)
{
    static float lastInputTime[GLFW_KEY_LAST] = {0};
    float currentTime = (float)glfwGetTime();

    for (int i = 0; i < num_combinations; i++) {
        bool allKeysPressed = true;
        for (int j = 0; key_combinations[i][j] != -1; j++) {
            if (!keyboard_isKeyPressed(window, key_combinations[i][j])) {
                allKeysPressed = false;
                break;
            }
        }

        if (allKeysPressed && currentTime - lastInputTime[key_combinations[i][0]] >= debounceTimes[i]) {
            va_list args;
            va_start(args, num_combinations);
            call_backs[i](args);
            va_end(args);
            lastInputTime[key_combinations[i][0]] = currentTime;
        }
    }
}
