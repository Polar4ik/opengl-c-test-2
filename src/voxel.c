#include "voxel.h"

Voxel create_voxel() {
    Voxel voxel;

    memcpy(voxel.vertices, voxel_vertices, sizeof(voxel_vertices));
    memcpy(voxel.normals, voxel_normals, sizeof(voxel_normals));
    memcpy(voxel.indices, voxel_indices, sizeof(voxel_indices));

    return voxel;
}
