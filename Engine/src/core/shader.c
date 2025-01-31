#include "core/shader.h"

static char *read_file(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        printf("Failed to open file");
        exit(EXIT_FAILURE);
    }
    struct stat st;

    if (stat(filepath, &st) < 0) {
        perror("Failed to get file stats");
        close(fd);
        exit(EXIT_FAILURE);
    }
    char *buffer = malloc(sizeof(char) * st.st_size + 1);
    if (!buffer) {
        perror("Failed to malloc memory for buffer");
        close(fd);
        exit(EXIT_FAILURE);
    }
    ssize_t bytes = read(fd, buffer, st.st_size);
    if (bytes < 0) {
        perror("Failed to read file");
        free(buffer);
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes] = '\0';
    close(fd);
    return buffer;
}

static GLuint create_vs(const char *filepath)
{
    GLint params;
    GLchar info_log[GL_INFO_LOG_LENGTH];

    char *vs_source = read_file(filepath);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, (const GLchar * const *)&vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(vs, GL_INFO_LOG_LENGTH, NULL, info_log);
        perror("Failed to compile vertex shader");
        exit(EXIT_FAILURE);
    }
    free(vs_source);
    return vs;
}

static GLuint create_fs(const char *filepath)
{
    GLint params;
    GLchar info_log[GL_INFO_LOG_LENGTH];

    char *fs_source = read_file(filepath);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, (const GLchar * const *)&fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (!params) {
        glGetShaderInfoLog(fs, GL_INFO_LOG_LENGTH, NULL, info_log);
        perror("Failed to compile fragment shader");
        exit(EXIT_FAILURE);
    }
    free(fs_source);
    return fs;
}

static GLuint create_program(GLuint *vs, GLuint *fs)
{
    GLint params;
    GLchar info_log[GL_INFO_LOG_LENGTH];

    GLuint program = glCreateProgram();
    glAttachShader(program, *vs);
    glAttachShader(program, *fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (!params) {
        glGetProgramInfoLog(program, GL_INFO_LOG_LENGTH, NULL, info_log);
        perror("Failed to link program");
        exit(EXIT_FAILURE);
    }
    glValidateProgram(program);
    glDeleteShader(*vs);
    glDeleteShader(*fs);
    return program;
}


shader_s *shader_create(window_s* window, const char *vs_filepath, const char *fs_filepath)
{
    shader_s *shader = malloc(sizeof(shader_s));
    GLuint vs = create_vs(vs_filepath);
    GLuint fs = create_fs(fs_filepath);
    shader->program = create_program(&vs, &fs);
    shader_setortho(shader, (int)window->size.x, (int)window->size.y);
    return shader;
}

void shader_use(shader_s *shader)
{
    glUseProgram(shader->program);
}

GLuint shader_get(shader_s *shader)
{
    return shader->program;
}

void shader_delete(shader_s *shader)
{
    glDeleteShader(shader->program);
    free(shader);
}

void shader_setortho(shader_s *shader, int width, int height)
{
    mat4 ortho;
    glm_ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f, ortho);
    shader_mat4fv(shader, "uProjection", ortho);
}

void shader_mat4fv(shader_s *shader, const char *name, mat4 matrix)
{
    shader_use(shader);
    glUniformMatrix4fv(glGetUniformLocation(shader_get(shader), name), 1, GL_FALSE, matrix[0]);
}

void shader_vec4f(shader_s *shader, const char *name, float x, float y, float z, float w)
{
    shader_use(shader);
    glUniform4f(glGetUniformLocation(shader_get(shader), name), x, y, z, w);
}

void shader_vec2f(shader_s *shader, const char *name, float x, float y)
{
    shader_use(shader);
    glUniform2f(glGetUniformLocation(shader_get(shader), name), x, y);
}

void shader_vec3f(shader_s *shader, const char *name, float x, float y, float z)
{
    shader_use(shader);
    glUniform3f(glGetUniformLocation(shader_get(shader), name), x, y, z);
}

void shader_1f(shader_s *shader, const char *name, float x)
{
    shader_use(shader);
    glUniform1f(glGetUniformLocation(shader_get(shader), name), x);
}

void shader_1i(shader_s *shader, const char *name, int x)
{
    shader_use(shader);
    glUniform1i(glGetUniformLocation(shader_get(shader), name), x);
}

void shader_bool(shader_s *shader, const char *name, bool x)
{
    shader_use(shader);
    glUniform1i(glGetUniformLocation(shader_get(shader), name), x);
}
