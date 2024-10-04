#ifndef BLOCK_H
#define BLOCK_H

#include "voxel.h"
#include <cglm/cglm.h>

typedef enum {
    BLOCK_AIR = 0,
    BLOCK_GRASS,
} BlockType;

typedef struct {
    Voxel voxel;
    vec3 block_position;
    BlockType block_type; 
} Block;

Block create_block(vec3 position, BlockType type);

#endif
