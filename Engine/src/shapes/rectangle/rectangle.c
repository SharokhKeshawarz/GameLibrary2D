#include "shapes/rectangle.h"

rectangle_s* rectangle_create(void)
{
    rectangle_s* rectangle = malloc(sizeof(rectangle_s));
    if (rectangle == NULL) {
        log_error("Failed To Init Rectangle");
        exit(EXIT_FAILURE);
    }

    glm_mat4_identity(rectangle->model);

    float vertices[16] = {
        // POS      // Tex
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    };
    
    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    memcpy(rectangle->vertices, vertices, sizeof(vertices));
    memcpy(rectangle->indices, indices, sizeof(indices));

    rectangle->vao = vao_create();
    rectangle->vbo = vbo_create();
    rectangle->ebo = ebo_create();

    vao_bind(rectangle->vao);

    vbo_bind(rectangle->vbo);
    vbo_data(sizeof(rectangle->vertices), rectangle->vertices);

    ebo_bind(rectangle->ebo);
    ebo_data(sizeof(rectangle->indices), rectangle->indices);
    
    vao_attribpointer(0, 2, 4, 0);
    vao_attribpointer(1, 2, 4, 2);

    vao_unbind();
    vbo_unbind();
    ebo_unbind();

    for (int i = 0; i < 4; i++) rectangle->color.v[i] = -1.0f;
    for (int i = 0; i < 2; i++) rectangle->position.v[i] = 0.0f;
    for (int i = 0; i < 2; i++) rectangle->size.v[i] = 0.0f;
    for (int i = 0; i < 2; i++) rectangle->rotation.v[i] = 0.0f;
    for (int i = 0; i < 2; i++) rectangle->scale.v[i] = 1.0f;
    for (int i = 0; i < 2; i++) rectangle->origin.v[i] = 0.0f;


    rectangle->textureID = 0;
    rectangle->hasTexture = false;

    rectangle->rect.top = 0.0f;
    rectangle->rect.left = 0.0f;
    rectangle->rect.width = 0.0f;
    rectangle->rect.height = 0.0f;

    for (int i = 0; i < 4; i++) rectangle->outlineColor.v[i] = -1.0f;
    rectangle->outlineThickness = 0.0f;
    rectangle->hasOutline = false;
    
    return rectangle;
}


rectangle_s* rectangle_outline(rectangle_s* rectangle)
{
    rectangle_s* outlineRectangle = rectangle_create();

    rectangle_setColor(outlineRectangle, rectangle->outlineColor);

    vec2_s outlineSize = (vec2_s){
        rectangle->size.v[X] + rectangle->outlineThickness,
        rectangle->size.v[Y] + rectangle->outlineThickness
    };
    rectangle_setSize(outlineRectangle, outlineSize);

    rectangle_setOrigin(outlineRectangle, rectangle->origin);
    rectangle_setScale(outlineRectangle, rectangle->scale);
    rectangle_setRotation(outlineRectangle, rectangle->rotation.v[DEG]);

    vec2_s outlinePosition = (vec2_s){
        rectangle->position.v[X] - 25.0f * rectangle->outlineThickness,
        rectangle->position.v[Y] - 25.0f * rectangle->outlineThickness
    };
    rectangle_setPosition(outlineRectangle, outlinePosition);

    return outlineRectangle;
}

static bool is_rectangle_on_screen(rectangle_s *rectangle, int window_width, int window_height)
{
    float rect_left = rectangle->position.v[0];
    float rect_right = rectangle->position.v[0] + rectangle->size.v[0] * rectangle->scale.v[0];
    float rect_top = rectangle->position.v[1];
    float rect_bottom = rectangle->position.v[1] + rectangle->size.v[1] * rectangle->scale.v[1];

    if (rect_right < 0 || rect_left > window_width || rect_bottom < 0 || rect_top > window_height)
        return false;
    return true;
}

void rectangle_draw(window_s* window, rectangle_s* rectangle, shader_s* shader)
{
//    if (is_rectangle_on_screen(
//            rectangle,
//            (int)window->size.v[0],
//            (int)window->size.v[1]
//        ) == false
//    ) return;

    if (rectangle->hasOutline) {
        rectangle_s* outlineRectangle = rectangle_outline(rectangle);
        
        shader_vec4f(shader, "color", 
            outlineRectangle->color.v[X],
            outlineRectangle->color.v[Y],
            outlineRectangle->color.v[Z],
            outlineRectangle->color.v[W]
        );

        shader_bool(shader, "hasTexture", false);
        shader_mat4fv(shader, "model", outlineRectangle->model);

        vao_bind(outlineRectangle->vao);
        vbo_bind(outlineRectangle->vbo);
        ebo_bind(outlineRectangle->ebo);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        vao_unbind();
        vbo_unbind();
        ebo_unbind();

        free(outlineRectangle);
    }

    shader_bool(shader, "hasTexture", rectangle->hasTexture);
    shader_vec4f(
        shader,
        "color", 
        rectangle->color.v[X], 
        rectangle->color.v[Y], 
        rectangle->color.v[Z], 
        rectangle->color.v[W]
    );
    if (rectangle->hasTexture)
        texture_activate(rectangle->textureID, 0, shader);
    shader_mat4fv(shader, "model", rectangle->model);
    vao_bind(rectangle->vao);
    vbo_bind(rectangle->vbo);
    ebo_bind(rectangle->ebo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    vao_unbind();
    vbo_unbind();
    ebo_unbind();
}

static void draw_quad(float* vertices, unsigned int* indices, unsigned int textureID, shader_s* shader)
{
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 16, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Draw the elements
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void rectangle_draw_texture_rect(texture_s* texture, rect_float_s rect, shader_s* shader)
{
    // Full-screen quad for the texture
    float vertices[] = {
        // Position     // Texture Coords
        0.0f, 0.0f,      0.0f, 0.0f,  // Bottom-left
        texture->width, 0.0f,      1.0f, 0.0f,  // Bottom-right
        texture->width, texture->height, 1.0f, 1.0f,  // Top-right
        0.0f, texture->height, 0.0f, 1.0f   // Top-left
    };

    unsigned int indices[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    // Texture rect (convert to normalized coordinates for rendering)
    float u1 = rect.left / texture->width;
    float v1 = rect.top / texture->height;
    float u2 = (rect.left + rect.width) / texture->width;
    float v2 = (rect.top + rect.height) / texture->height;

    float rectVertices[] = {
        // Position      // Texture Coords
        rect.left, rect.top,           u1, v1,  // Bottom-left
        rect.left + rect.width, rect.top,           u2, v1,  // Bottom-right
        rect.left + rect.width, rect.top + rect.height, u2, v2,  // Top-right
        rect.left, rect.top + rect.height, u1, v2   // Top-left
    };

    // Bind shader and send data
    shader_use(shader);

    // Draw the texture as a full-screen quad
    draw_quad(vertices, indices, texture->id, shader);

    // Draw the texture rectangle outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set to wireframe mode
    draw_quad(rectVertices, indices, 0, shader); // No texture, just outline
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Reset to fill mode
}


void rectangle_destroy(rectangle_s* rectangle)
{
    vao_delete(rectangle->vao);
    vbo_delete(rectangle->vbo);
    ebo_delete(rectangle->ebo);
    free(rectangle);
}
