#if !defined(_L_GRAPHICS_MAIN_LOOP_H)
#define _L_GRAPHICS_MAIN_LOOP_H

#include "graphics_internal.h"
#include "mesh_obj.h"

void loop(void);
void input(bool *is_working);
void prepare(void);
void draw(mesh_object_t *mesh, GLuint shader_program);

#endif // _L_GRAPHICS_MAIN_LOOP_H
