#include "../../Engine/include/Window/window.h"
#include "../../Engine/include/Input/keyboard.h"
#include "../../Engine/include/Input/mouse.h"
#include "../../Engine/include/shapes/rectangle.h"
#include "../../Engine/include/shapes/rect.h"


typedef enum player_stat_e {
    IDLE,
    WALKING,
    ATTACKING
} player_stat_e;

typedef struct player_s
{
    rectangle_s* this;
    rectangle_s* hitbox;

    texture_s* texture;
    rect_float_s rect;

    vec2_s hitboxScaleFactor;
    player_stat_e stat;
    bool isMoving;
} player_s;

player_s* player_init(char* spritesheed)
{
    player_s* player = malloc(sizeof(player_s));

    player->this = rectangle_create();
    player->hitbox = rectangle_create();

    player->texture = texture_load(spritesheed);
    player->rect = (rect_float_s){0.0f, 0.0f, 0.0f, 0.0f};

    player->hitboxScaleFactor = (vec2_s){0.5f, 0.5f};
    player->stat = IDLE;
    player->isMoving = false;
    return player;
}

void player_draw(window_s* window, player_s* player, shader_s* shader)
{
    rectangle_draw(window, player->this, shader);
    rectangle_draw(window, player->hitbox, shader);
}

void player_destroy(player_s* player)
{
    rectangle_destroy(player->this);
    rectangle_destroy(player->hitbox);
    texture_delete(player->texture);
    free(player);
}

int main(int argc, char const *argv[])
{
    window_s* window = window_create(800, 600, "Game", false);
    shader_s* shader = shader_create(window, "shaders/default_vert.glsl", "shaders/default_frag.glsl");
    
    // 288x480 --- 48x48 --- 288/6 x 480/10
    player_s* player = player_init("assets/sprites/characters/player.png");
    rectangle_setSize(player->this, (vec2_s){50.0f, 50.0f});
    rectangle_setScale(player->this, (vec2_s){2.0f, 2.0f});
    rectangle_setPosition(player->this, (vec2_s){20.0f, 20.0f});
    rectangle_setTexture(player->this, player->texture);
    rectangle_setTextureRect(player->this, player->texture, (rect_float_s){0, 0, 48, 48}, FLIP_HORIZONTAL);

    int idleWidth = player->texture->width/6;
    int idleHeight = player->texture->height/10;
    int idleFrames = 6;
    int idleCurrentFrame = 0;
    rect_float_s idleRect = {48, 0, 48, 48};
    

    float frameTime = 0.08f;
    double elapsedTime = 0.0;

    while (!window_shouldClose(window)) {
        double deltaTime = window_getDeltaTime();
        elapsedTime += deltaTime;
        
        if (keyboard_isKeyPressed(window, KEY_D) && player->stat != WALKING) {
            player->isMoving = true;
            player->stat = WALKING;
            idleCurrentFrame = 0;
            idleRect = (rect_float_s){48*4, 0, 48, 48};
        }
        if (keyboard_isKeyPressed(window, KEY_A) && player->stat != WALKING) {
            player->isMoving = true;
            player->stat = WALKING;
            idleCurrentFrame = 0;
            idleRect.left = 0;
            idleRect = (rect_float_s){48*4, 0, 48, 48};
        }

        if (keyboard_isKeyReleased(window, KEY_D) && keyboard_isKeyReleased(window, KEY_A) && player->stat != IDLE) {
            player->stat = IDLE;
            player->isMoving = false;
            idleCurrentFrame = 0;
            idleRect.left = 0;
            idleRect = (rect_float_s){0, 0, 48, 48};     
        }

        if (player->stat == WALKING) {
            if (elapsedTime > frameTime) {
                elapsedTime = 0.0f;
                idleCurrentFrame = (idleCurrentFrame + 1) % idleFrames;
                idleRect.left = idleCurrentFrame * idleWidth;
                if (keyboard_isKeyPressed(window, KEY_A))
                    rectangle_setTextureRect(player->this, player->texture, idleRect, FLIP_HORIZONTAL);
                else rectangle_setTextureRect(player->this, player->texture, idleRect, FLIP_NONE);         
            }
        }

        if (player->stat == IDLE) {
            if (elapsedTime > frameTime) {
                elapsedTime = 0.0f;
                idleCurrentFrame = (idleCurrentFrame + 1) % idleFrames;
                idleRect.left = idleCurrentFrame * idleWidth;
                rectangle_setTextureRect(player->this, player->texture, idleRect, FLIP_HORIZONTAL);
            }
        }


        window_clear(0.1f, 0.2f, 0.3f, 1.0f);

        player_draw(window, player, shader);


        window_display(window, KEY_ESCAPE);
        window_showFps();
    }

    window_destroy(window);
    return 0;
}
