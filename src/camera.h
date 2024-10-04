#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    float speed;
    float yaw;
    float pitch;
    float sensitivity;
    float lastX;
    float lastY;
    int firstMouse;
} Camera;

void initCamera(Camera* camera, float posX, float posY, float posZ);

void processInput(GLFWwindow* window, Camera* camera);

void mouseCallback(GLFWwindow* window, double xpos, double ypos, Camera* camera);

#endif
