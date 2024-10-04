#include "block.h"

Block create_block(vec3 position, BlockType type) {
    Block block;

    block.voxel = create_voxel();
    glm_vec3_copy(position, block.block_position);
    block.block_type = type;

    return block;
}
