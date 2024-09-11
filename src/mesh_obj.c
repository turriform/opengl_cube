#include "mesh_obj.h"

static void mesh_object_physics_create(mesh_object_t *mesh)
{
    mat4 init = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    glm_mat4_copy(init, mesh->physics.model);

    // setting inital world position
    glm_rotate(mesh->physics.model, glm_rad(50), (vec3){0.4, 1, 0});

    glm_mat4_copy(init, mesh->physics.view);

    glm_translate(mesh->physics.view, (vec3){0, 0, -7});
    glm_mat4_copy(init, mesh->physics.projection);
    glm_perspective(glm_rad(60), 1, 0.1, 10, mesh->physics.projection);
    // glm_perspective_default(1, mesh->physics.projection);
    // glm_perspective_default_rh_no(1, mesh->physics.projection);
}

void mesh_object_print(mesh_object_t *mesh)
{
    printf("\nWorld\n");
    glm_mat4_print(mesh->physics.model, stdout);

    printf("\nView\n");
    glm_mat4_print(mesh->physics.view, stdout);

    printf("\nPerspective\n");
    glm_mat4_print(mesh->physics.projection, stdout);
}

void mesh_object_create(mesh_object_t *mesh)
{

    GLfloat vertex[24] = {1, -1, 1,
                          -1, -1, 1,
                          1, 1, 1,
                          -1, 1, 1,
                          1, -1, -1,
                          -1, -1, -1,
                          1, 1, -1,
                          -1, 1, -1};

    GLfloat vertex_rgb[24] = {1, 1, 0,
                              0, 1, 0,
                              0, 0, 1,
                              1, 1, 0,
                              0, 1, 0,
                              0, 0, 1,
                              1, 0, 1,
                              0, 0, 1};

    GLint triangles[36] = {0, 2, 3, 0, 3, 1,
                           2, 6, 7, 2, 7, 3,
                           6, 4, 5, 6, 5, 7,
                           4, 0, 1, 4, 1, 5,
                           1, 3, 7, 1, 7, 5,
                           4, 6, 2, 4, 2, 0};

    glGenVertexArrays(1, &mesh->vertex_id);
    glBindVertexArray(mesh->vertex_id);

    glGenBuffers(1, &mesh->vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), (const GLvoid *)vertex, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &mesh->color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->color_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_rgb), (const GLvoid *)vertex_rgb, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &mesh->elementbuffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

    mesh->vertex_sz = 36;

    // clean
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    mesh_object_physics_create(mesh);

    mesh->rot = 0;
}

void mesh_object_draw(mesh_object_t *mesh, GLuint shader_program)
{
    glUseProgram(shader_program);

    GLuint u_model = glGetUniformLocation(shader_program, "model");
    glUniformMatrix4fv(u_model, 1, GL_FALSE, (float *)mesh->physics.model);

    GLuint u_view = glGetUniformLocation(shader_program, "view");
    glUniformMatrix4fv(u_view, 1, GL_FALSE, (float *)mesh->physics.view);

    GLuint u_projection = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, (float *)mesh->physics.projection);

    glBindVertexArray(mesh->vertex_id);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer_id);
    // glDrawArrays(GL_TRIANGLES, 0, 9);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer_id);
    glDrawElements(GL_TRIANGLES, mesh->vertex_sz, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
}

void mesh_object_rotate(mesh_object_t *mesh)
{
    mesh->rot += 1;
    mesh->rot /= 1000;
    glm_rotate(mesh->physics.model, glm_rad(50) * mesh->rot, (vec3){0, 0, 0.2});
}

void mesh_object_free(mesh_object_t *mesh)
{

    glDeleteBuffers(1, &mesh->vertex_buffer_id);
    glDeleteBuffers(1, &mesh->color_buffer_id);
    glDeleteVertexArrays(1, &mesh->elementbuffer_id);
}
