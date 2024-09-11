#if !defined(_L_GRAPHICS_INTERNAL_H)
#define _L_GRAPHICS_INTERNAL_H
#include "glad/glad.h"
#include "cglm/cglm.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#define GRAPHICS_CHAR_BUF 4096U
#define GRAPHICS_SHADER_BUF 16U * 1024U
#define GRAPHICS_QUAD_ARR_SZ 24U 
#define GRAPHICS_TRI_ARR_SZ 36U

#define SHADERS_PATH "./shaders"

#define OBJ_PATH "./obj"

#define GLTF_PATH "./gltf"
#define GLTF_PATH_MAX 512U
#define GLTF_ALLOCATORS 4U
#define BUF_URI_SZ 256U

#define str_n_cat(dest, src) (strncat((char *)(dest), (const char *)(src), (strlen((const char *)(src)) + 1)))
#define str_n_cmp(dest, src) (strncmp((char *)(dest), (const char *)(src), strlen((const char *)(src))))


extern SDL_Window *g_window;
extern SDL_GLContext *g_gl_context;

typedef enum Status
{
    STATUS_ok,
    STATUS_shader,
    STATUS_exit,
    STATUS_gltf,
    STATUS_err

} status_t;

#define STATUS_CRITICAL STATUS_err

typedef struct
{
    char title[256];
    int x;
    int y;
    int w;
    int h;

    Uint32 flags;

} window_t;



void graphics_internal_status(status_t status, const char *message);


#endif // _L_GRAPHICS_INTERNAL_H
