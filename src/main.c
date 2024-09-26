#define GLEW_STATIC

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdio.h>

int main() {
    if (!glfwInit()) {
        printf("Failed to init GLFW");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Example", NULL, NULL);
    if (!window) {
        printf("Failed to init window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialization error\n");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.74f, 1.0f, 1.0f);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}