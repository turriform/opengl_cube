#if !defined(_L_GRAPHICS_OBJ_H)
#define _L_GRAPHICS_OBJ_H
#include "graphics_internal.h"

typedef struct MeshObject
{

    GLuint vertex_id;
    GLuint vertex_buffer_id;
    GLuint color_buffer_id;
    GLuint elementbuffer_id;
    GLsizei vertex_sz;

    struct
    {
        mat4 model;
        mat4 view;
        mat4 projection;
    } physics;

    float rot;

} mesh_object_t;

void mesh_object_create(mesh_object_t *mesh);
void mesh_object_free(mesh_object_t *mesh);
void mesh_object_draw(mesh_object_t *mesh, GLuint shader_program);
void mesh_object_print(mesh_object_t *mesh);


void mesh_object_rotate(mesh_object_t *mesh);
#endif // _L_GRAPHICS_OBJ_H
