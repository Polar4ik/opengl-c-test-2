#include<string.h>

typedef struct {
    float vertices[8][3];
    float normals[6][3];
    unsigned int indices[36];
} Voxel;

const float voxel_vertices[8][3] = {
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 1.0f}
};

const float voxel_normals[6][3] = {
    { 0.0f,  0.0f, -1.0f},
    { 0.0f,  0.0f,  1.0f},
    { 1.0f,  0.0f,  0.0f},
    {-1.0f,  0.0f,  0.0f},
    { 0.0f,  1.0f,  0.0f},
    { 0.0f, -1.0f,  0.0f}
};

const unsigned int voxel_indices[36] = {
    0, 1, 2, 0, 2, 3,  
    4, 5, 6, 4, 6, 7,
    1, 5, 6, 1, 6, 2,
    0, 4, 7, 0, 7, 3,
    3, 2, 6, 3, 6, 7,
    0, 1, 5, 0, 5, 4
};

Voxel create_voxel() {
    Voxel voxel;

    memcpy(voxel.vertices, voxel_vertices, sizeof(voxel_vertices));
    memcpy(voxel.normals, voxel_normals, sizeof(voxel_normals));
    memcpy(voxel.indices, voxel_indices, sizeof(voxel_indices));

    return voxel;
}
