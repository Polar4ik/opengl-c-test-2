#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow* handle;
    int width;
    int height;
    const char* title;
} Window;

int init_window(Window* window, int width, int height, const char* title);

void process_window_events(Window* window);

#endif
