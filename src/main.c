
#include "graphics_internal.h"
#include "sdl_context.h"
#include "shader_program.h"
#include "loop.h"

int main(void)
{

    window_t win_params = (window_t){"Almost Companion Cube",
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     500, 500, SDL_WINDOW_OPENGL};

    sdl_init();

    sdl_window_init(win_params);
    sdl_gl_context_init();

 

    loop();

    sdl_clean();
}