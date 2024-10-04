#include "shader_loader.h"

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

unsigned int buildShaders() {
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

    return shaderProgram;
}
