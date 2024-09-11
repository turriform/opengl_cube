#include "shader_program.h"
#include "loop.h"
#include "mesh_obj.h"

void input(bool *is_working)
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *is_working = false;
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {

            *is_working = false;
        }
    }
}
void prepare(void)
{

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, 500, 500);
}
void draw(mesh_object_t *mesh, GLuint shader_program)
{
    mesh_object_draw(mesh, shader_program);
}

void loop(void)
{
    GLuint shader_program = graphics_shader_loader("vertex.glsl", "fragment.glsl");
    mesh_object_t mesh = (mesh_object_t){0};
    mesh_object_create(&mesh);
    mesh_object_print(&mesh);
    bool is_working = true;

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    
    while (is_working)
    {

        prepare();

        mesh_object_rotate(&mesh);

        input(&is_working);

        draw(&mesh, shader_program);

        SDL_GL_SwapWindow(g_window);
    }
    glDeleteProgram(shader_program);
    mesh_object_free(&mesh);

    printf("End of loop \n");
}
