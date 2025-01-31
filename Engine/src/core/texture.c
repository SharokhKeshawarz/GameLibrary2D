#include "core/texture.h"

texture_s* texture_create(char* path)
{
    texture_s* texture = malloc(sizeof(texture_s));

    glGenTextures(1, &texture->id);
    texture->width = 0;
    texture->height = 0;
    texture->channels_in_file = 0;
    texture->path = malloc(sizeof(char) * strlen(path));
    strcpy(texture->path, path);
    return texture;
}

void texture_bind(texture_t id)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void texture_parameter(texture_s* texture, GLint xAxis, GLint yAxis, GLint filterMin, GLint filterMag)
{
    unsigned char* data = stbi_load(texture->path, &texture->width, &texture->height, &texture->channels_in_file, 0);
    if (data == NULL || !data) {
        printf("Failed To Load Texture: %s\n", texture->path);
        exit(EXIT_FAILURE);
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, xAxis);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, yAxis);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);

    GLenum format = (texture->channels_in_file == 3) ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void texture_activate(texture_t id, int index, shader_s* shader)
{
    char indexToString[31];
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
    shader_use(shader);
    sprintf(indexToString, "texture%d", index);
    shader_1i(shader, indexToString, index);
}

void texture_unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void texture_delete(texture_s* texture)
{
    glDeleteTextures(1, &texture->id);
    free(texture->path);
    free(texture);
}

texture_s* texture_load(char* path)
{
    texture_s* texture = texture_create(path);
    texture_bind(texture->id);
    texture_parameter(texture, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST);
    texture_unbind();
    return texture;
}
