#ifndef VOXEL_H
#define VOXEL_H

#include <string.h>

typedef struct {
    float vertices[8][3];
    float normals[6][3];
    unsigned int indices[36];
} Voxel;

extern const float voxel_vertices[8][3];
extern const float voxel_normals[6][3];
extern const unsigned int voxel_indices[36];

Voxel create_voxel(void);

#endif
