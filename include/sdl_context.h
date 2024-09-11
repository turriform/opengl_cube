#if !defined(_L_SDL_CONTEXT_H_)
#define _L_SDL_CONTEXT_H_
#include "graphics_internal.h"



void sdl_init(void);
void sdl_clean(void);
void sdl_window_init(window_t win);
void sdl_gl_context_init(void);



#endif // _L_SDL_CONTEXT_H_


