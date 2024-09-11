#include "sdl_context.h"

SDL_Window *g_window = NULL;
SDL_GLContext *g_gl_context = NULL;

void graphics_internal_status(status_t status, const char *message)
{
    const char *sdl_error = SDL_GetError();

    if (status >= STATUS_CRITICAL || strlen(sdl_error) > 0)
    {
        printf("%s\n", message);
        printf("Sdl error: %s\n\n", sdl_error);
        printf("Critical error... exiting\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", message);
    if (status == STATUS_exit)
    {
        exit(EXIT_SUCCESS);
    }
}

static inline void opengl_clear_err(void)
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool opengl_get_err_status(void)
{
    opengl_clear_err();

    return true;
}

///////////////////////////////////

void sdl_init(void)
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        graphics_internal_status(STATUS_err, "Could not init SDL");
    }

    graphics_internal_status(STATUS_ok, "SDL init ok");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void sdl_clean(void)
{
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    graphics_internal_status(STATUS_ok, "SDL quit");
}

void sdl_window_init(window_t win)
{
    g_window = SDL_CreateWindow(win.title, win.x, win.y, win.w, win.h, win.flags);
    if (g_window == NULL)
    {
        graphics_internal_status(STATUS_err, "Window could not be initialized");
    }
    graphics_internal_status(STATUS_ok, "Window Set up ok");
}

void sdl_gl_context_init(void)
{
    g_gl_context = SDL_GL_CreateContext(g_window);
    if (g_gl_context == NULL)
    {
        graphics_internal_status(STATUS_err, "Context creation failed");
    }
    graphics_internal_status(STATUS_ok, "Context created");

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        graphics_internal_status(STATUS_err, "Could not init GLAD");
    }

    printf(
        "\nOpenGL info context information\nVendor\t\t\t%s\nVersion\t\t\t%s\nRenderer\t\t%s\nShading language v\t%s\n\n",
        glGetString(GL_VENDOR),
        glGetString(GL_VERSION),
        glGetString(GL_RENDERER),
        glGetString(GL_SHADING_LANGUAGE_VERSION));
}