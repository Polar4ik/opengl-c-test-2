#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

char* loadShaderSource(const char* filename);
void checkShaderCompilation(unsigned int shader);
void checkProgramLinking(unsigned int program);
unsigned int buildShaders();

#endif