#include "camera.h"
#include <stdio.h>
#include <math.h>

void init_camera(Camera* camera, float posX, float posY, float posZ) {
    glm_vec3_copy((vec3){posX, posY, posZ}, camera->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera->front);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera->up);
    camera->speed = 0.05f;
    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
    camera->lastX = 400;
    camera->lastY = 300;
    camera->firstMouse = 1;
    camera->sensitivity = 0.1f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos, Camera* camera) {
    if (camera->firstMouse) {
        camera->lastX = xpos;
        camera->lastY = ypos;
        camera->firstMouse = 0;
    }

    float xoffset = xpos - camera->lastX;
    float yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;

    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    vec3 front;
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize_to(front, camera->front);
}

void processInput(GLFWwindow* window, Camera* camera) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_add(camera->position, (vec3){camera->speed * camera->front[0], camera->speed * camera->front[1], camera->speed * camera->front[2]}, camera->position);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_sub(camera->position, (vec3){camera->speed * camera->front[0], camera->speed * camera->front[1], camera->speed * camera->front[2]}, camera->position);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_crossn(camera->front, camera->up, cameraRight);
        glm_vec3_sub(camera->position, (vec3){camera->speed * cameraRight[0], camera->speed * cameraRight[1], camera->speed * cameraRight[2]}, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_crossn(camera->front, camera->up, cameraRight);
        glm_vec3_add(camera->position, (vec3){camera->speed * cameraRight[0], camera->speed * cameraRight[1], camera->speed * cameraRight[2]}, camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->position[1] += camera->speed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->position[1] -= camera->speed;
}
