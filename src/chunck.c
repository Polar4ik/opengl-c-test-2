#include "chunk.h"

void init_chunk(Chunk* chunk, vec3 position) {
    glm_vec3_copy(position, chunk->position);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                chunk->blocks[x][y][z] = (Block){0};
                init_block_renderer(&chunk->blocks[x][y][z].renderer);
            }
        }
    }
}

void set_block(Chunk* chunk, int x, int y, int z, BlockType type) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return;
    }
    
    chunk->blocks[x][y][z].block_type = type;
    chunk->blocks[x][y][z].voxel = create_voxel();
}

Block get_block(const Chunk* chunk, int x, int y, int z) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return (Block){0};
    }
    return chunk->blocks[x][y][z];
}

void render_chunk(const Chunk* chunk) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                Block block = chunk->blocks[x][y][z];
                if (block.block_type != BLOCK_AIR) {
                    block.block_position[0] = chunk->position[0] + x;
                    block.block_position[1] = chunk->position[1] + y;
                    block.block_position[2] = chunk->position[2] + z;
                    render_block(&block.renderer);
                }
            }
        }
    }
}

void cleanup_chunk(Chunk* chunk) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                cleanup_block_renderer(&chunk->blocks[x][y][z].renderer);
            }
        }
    }
}
