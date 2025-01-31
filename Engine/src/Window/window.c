#include "Window/window.h"
#include "Input/mouse.h"

window_s* window_create(int width, int height, char* title, bool resizable)
{

    if (!glfwInit()) {
        perror("Failed to init glfw");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init audio");
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed To Init Aduio Device\n");
        exit(EXIT_FAILURE);
    }

    window_s* window = (window_s*)malloc(sizeof(window_s));

    window->size.x = width;
    window->size.y = height;

    window->title = (char*)malloc(sizeof(char) * (strlen(title) + 1));
    strcpy(window->title, title);


    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window->window);
    glfwSwapInterval(0);
    glfwGetWindowPos(window->window, (int*)&window->posision.x, (int*)&window->posision.y);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("Failed to init glad");
        exit(EXIT_FAILURE);
    }
    glViewport(0, 0, (int)window->size.x, (int)window->size.y);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    stbi_set_flip_vertically_on_load(false);
    glfwSetScrollCallback(window->window, callback_scroll);
    return window;
}

vec2_s window_getSize(window_s* window)
{
    return window->size;
}

int window_getWidth(window_s* window)
{
    return (int)window->size.x;
}


int window_getHeight(window_s* window)
{
    return (int)window->size.y;
}

vec2_s window_getPosition(window_s* window)
{
    return window->posision;
}

int window_getPositionX(window_s* window)
{
    return (int)window->posision.x;
}

int window_getPositionY(window_s* window)
{
    return (int)window->posision.y;
}

char *window_getTitle(window_s* window)
{
    return window->title;
}

bool window_shouldClose(window_s* window)
{
    return glfwWindowShouldClose(window->window);
}

void window_setFps(unsigned int target_fps)
{
    if (target_fps == 0) return;
    static double last_time = 0.0;
    double current_time = glfwGetTime();
    double frame_duration = 1.0 / target_fps;

    double elapsed_time = current_time - last_time;
    if (elapsed_time < frame_duration) {
        usleep((frame_duration - elapsed_time) * 1e6); // Convert seconds to microseconds
    }

    last_time = glfwGetTime();
}

void window_showFps()
{
    static double fps_time = 0.0;  // Time tracker for FPS calculation
    static int frame_count = 0;   // Frame counter

    if (fps_time == 0.0) {
        fps_time = glfwGetTime(); // Initialize fps_time on the first call
    }

    double current_time = glfwGetTime();

    // Check if 1 second has passed
    if (current_time - fps_time >= 1.0) {
        double fps = frame_count / (current_time - fps_time); // Calculate FPS
        printf("FPS: %.0f\n", fps);
        frame_count = 0;         // Reset frame count for the next second
        fps_time = current_time; // Reset fps_time to the current time
    }
    frame_count++; // Increment frame count
}

double window_getDeltaTime()
{
    static double previous_time = 0.0;

    if (previous_time == 0.0) previous_time = glfwGetTime();

    double current_time = glfwGetTime();
    double deltatime = current_time - previous_time;
    previous_time = current_time;
    return deltatime;
}

void window_clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void window_display(window_s* window, int quit_key)
{
    glfwSwapBuffers(window->window);
    glfwPollEvents();
    if (glfwGetKey(window->window, quit_key))
        glfwSetWindowShouldClose(window->window, GLFW_TRUE);
}

void window_quit(window_s* window, int key)
{
    if (glfwGetKey(window->window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window->window, GLFW_TRUE);
}

void window_destroy(window_s* window)
{
    free(window->title);
    glfwDestroyWindow(window->window);
    free(window);
    glfwTerminate();
}
