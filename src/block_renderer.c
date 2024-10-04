#include "block_renderer.h"
#include <cglm/cglm.h>
#include "shader_loader.h"

#include "camera.h"

void init_block_renderer(BlockRenderer* block_renderer) {
    glGenVertexArrays(1, &block_renderer->vao);
    glBindVertexArray(block_renderer->vao);

    glGenBuffers(1, &block_renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, block_renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(block_renderer->voxel.vertices), block_renderer->voxel.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &block_renderer->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block_renderer->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(block_renderer->voxel.indices), block_renderer->voxel.indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void render_block(const BlockRenderer* block_renderer, const Camera* camera) {
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, block_renderer->position);

    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

    mat4 view;
    vec3 target;
    glm_vec3_add(camera->position, camera->front, target);
    glm_lookat(camera->position, target, camera->up, view);

    unsigned int shaderProgram = buildShaders();

    glUseProgram(shaderProgram);
    
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)projection);
    glUniform3f(lightPosLoc, 0.0f, 3.0f, 5.0f); 


    glBindVertexArray(block_renderer->vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void cleanup_block_renderer(BlockRenderer* block_renderer) {
    glDeleteVertexArrays(1, &block_renderer->vao);
    glDeleteBuffers(1, &block_renderer->vbo);
    glDeleteBuffers(1, &block_renderer->ebo);
}
