#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "voxel.h"
#include "block_renderer.h"
#include <cglm/cglm.h>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

typedef struct {
    Block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    vec3 position;
} Chunk;

void init_chunk(Chunk* chunk, float x, float y, float z);
void set_block(Chunk* chunk, int x, int y, int z, BlockType type);
Block get_block(const Chunk* chunk, int x, int y, int z);
void render_chunk(const Chunk* chunk);
void cleanup_chunk(Chunk* chunk);

#endif
