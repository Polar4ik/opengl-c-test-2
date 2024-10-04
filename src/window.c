#include "window.h"
#include <stdio.h>
#include <stdlib.h>

int init_window(Window* window, int width, int height, const char* title) {
    window->width = width;
    window->height = height;
    window->title = title;

    if (!glfwInit()) {
        printf("Failed to init GLFW\n");
        return -1;
    }

    window->handle = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
    if (!window->handle) {
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window->handle);
    glfwSetInputMode(window->handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    return 0;
}

void process_window_events(Window* window) {
    if (glfwWindowShouldClose(window->handle)) {
        glfwSetWindowShouldClose(window->handle, GLFW_TRUE);
    }
    
    glfwPollEvents();
}

void cleanup_window(Window* window) {
    glfwDestroyWindow(window->handle);
    glfwTerminate();
}
