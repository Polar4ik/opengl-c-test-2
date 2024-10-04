#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <stdio.h>
#include <stdlib.h>

float cameraSpeed = 0.05f;
vec3 cameraPos = {0.0f, 0.0f, 3.0f};
vec3 cameraFront = {0.0f, 0.0f, -1.0f};
vec3 cameraUp = {0.0f, 1.0f, 0.0f};

float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
int firstMouse = 1;
float sensitivity = 0.1f;

int screenWidth = 800;
int screenHeight = 600;

float cubeAng = 0.0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = 0;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 front;
    front[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
    front[1] = sin(glm_rad(pitch));
    front[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    glm_normalize_to(front, cameraFront);
}

char* loadShaderSource(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* shaderSource = (char*)malloc(length + 1);
    if (!shaderSource) {
        printf("Failed to allocate memory for shader\n");
        fclose(file);
        return NULL;
    }

    fread(shaderSource, 1, length, file);
    shaderSource[length] = '\0';

    fclose(file);
    return shaderSource;
}

void checkShaderCompilation(unsigned int shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::COMPILATION_FAILED\n%s\n", infoLog);
    }
}

void checkProgramLinking(unsigned int program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        glm_vec3_add(cameraPos, (vec3){cameraSpeed * cameraFront[0], cameraSpeed * cameraFront[1], cameraSpeed * cameraFront[2]}, cameraPos);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glm_vec3_sub(cameraPos, (vec3){cameraSpeed * cameraFront[0], cameraSpeed * cameraFront[1], cameraSpeed * cameraFront[2]}, cameraPos);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_crossn(cameraFront, cameraUp, cameraRight);
        glm_vec3_sub(cameraPos, (vec3){cameraSpeed * cameraRight[0], cameraSpeed * cameraRight[1], cameraSpeed * cameraRight[2]}, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        vec3 cameraRight;
        glm_vec3_crossn(cameraFront, cameraUp, cameraRight);
        glm_vec3_add(cameraPos, (vec3){cameraSpeed * cameraRight[0], cameraSpeed * cameraRight[1], cameraSpeed * cameraRight[2]}, cameraPos);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos[1] += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos[1] -= cameraSpeed;
}

int main() {
    if (!glfwInit()) {
        printf("Failed to init GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Example", NULL, NULL);
    if (!window) {
        printf("Failed to init window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    unsigned int VAO, VBO, EBO;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, -1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        4, 6, 5,
        4, 7, 6,

        4, 0, 3,
        4, 3, 7,

        1, 5, 6,
        1, 6, 2,

        3, 2, 6,
        3, 6, 7,

        4, 5, 1,
        4, 1, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    char *vertexShaderCode = loadShaderSource("D:/All Projects/c_opengl_test_3/src/shaders/vertex.glsl");
    char *fragmentShaderCode = loadShaderSource("D:/All Projects/c_opengl_test_3/src/shaders/fragment.glsl");

    if (!vertexShaderCode || !fragmentShaderCode) {
        printf("Could not load shaders\n");
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);

    free(vertexShaderCode);
    free(fragmentShaderCode);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);
    
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        cubeAng += 0.01f;

        glClearColor(0.0f, 0.74f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view;
        vec3 target;
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        glm_vec3_add(cameraPos, cameraFront, target);
        glm_lookat(cameraPos, target, cameraUp, view);

        glm_rotate_y(model, cubeAng, model);

        glUseProgram(shaderProgram);
        
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)projection);
        glUniform3f(lightPosLoc, 0.0f, 3.0f, 5.0f); 

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
