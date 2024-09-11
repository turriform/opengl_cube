#include "shader_program.h"

GLchar *graphics_shader_load(const char *filename)
{
    char fullpath[1024] = "";
    str_n_cat(fullpath, SHADERS_PATH);
    str_n_cat(fullpath, "/");
    str_n_cat(fullpath, filename);

    printf("fullpath %s \n", fullpath);

    FILE *fp = fopen(fullpath, "r");
    if (fp == NULL)
    {
        graphics_internal_status(STATUS_err, "Cannot open shader file");
    }

    size_t size = 0;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    printf("Shader size %ld\n", size);
    GLchar *shader_src = calloc(size + 1, sizeof(GLchar));
    if (shader_src == NULL)
    {
        graphics_internal_status(STATUS_err, "Cannot allocate memory");
    }

    fread(shader_src, size, 1, fp);

    return shader_src;
}

GLint graphics_shader_compiled_status(GLuint shader_id)
{
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader_id, 1024, &log_length, message);
        graphics_internal_status(STATUS_shader, message);
    }

    graphics_internal_status(STATUS_ok, "Shader compiled");

    return compiled;
}

GLint graphics_shader_linked_status(GLuint program_id)
{
    GLint linked = GL_FALSE;
    glGetShaderiv(program_id, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(program_id, 1024, &log_length, message);
        graphics_internal_status(STATUS_shader, message);
    }

    graphics_internal_status(STATUS_ok, "Shader linked");

    return linked;
}

GLuint graphics_shader_loader(const char *vertex_shader, const char *fragment_shader)
{
    /*
        Returns shader program
        needs to be deleted later
        glDeleteProgram()
    */

    GLuint vertext_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    /*  VERTEX SHADER  */


    GLchar * vertex_shader_src = graphics_shader_load(vertex_shader);
    glShaderSource(vertext_shader_id, 1,  (const GLchar * const*)&vertex_shader_src, NULL);
    glCompileShader(vertext_shader_id);
    free(vertex_shader_src);


    graphics_shader_compiled_status(vertext_shader_id);

    /*  FRAMGMENT SHADER  */

    GLchar * frag_shader_src = graphics_shader_load(fragment_shader);
    glShaderSource(fragment_shader_id, 1, (const GLchar * const*)&frag_shader_src, NULL);
    glCompileShader(fragment_shader_id);
    free(frag_shader_src);

    graphics_shader_compiled_status(fragment_shader_id);

    /*   SHADER PROGRAM  */

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, vertext_shader_id);
    glAttachShader(shader_program, fragment_shader_id);
    glLinkProgram(shader_program);

    graphics_shader_linked_status(shader_program);

    glDetachShader(shader_program, vertext_shader_id);
    glDetachShader(shader_program, fragment_shader_id);

    glDeleteShader(vertext_shader_id);
    glDeleteShader(fragment_shader_id);

    return shader_program;
}