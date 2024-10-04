#ifndef BLOCK_RENDERER_H
#define BLOCK_RENDERER_H

#include <glad/glad.h>
#include "block.h"
#include "voxel.h"

typedef struct {
    Voxel voxel;
    vec3 position;
    BlockType type;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} BlockRenderer;

void init_block_renderer(BlockRenderer* block_renderer);
void render_block(const BlockRenderer* block_renderer);
void cleanup_block_renderer(BlockRenderer* block_renderer);

#endif
