// #pragma region COLLISION
// #include "core/main.h"
// #include "nuklear/nuklear_configs.h"
// #include "nuklear/nuklear.h"
// #include "nuklear/nuklear_glfw_gl3.h"
// #include "Window/window.h"
// #include "core/shader.h"
// #include "core/vao.h"
// #include "core/vbo.h"
// #include "core/ebo.h"
// #include "core/log.h"
// #include "core/texture.h"
// #include "Input/keyboard.h"
// #include "shapes/rectangle.h"

// #define MAX_SCALE 50.0f
// #define MIN_SCALE 2.0f

// void scaleBigger(va_list args) {
//     rectangle_s* rectangle = va_arg(args, rectangle_s*);
//     float* scaleIncrease = va_arg(args, float*);

//     vec2_s scale = rectangle_getScale(rectangle);
//     scale.x = fminf(scale.x + *scaleIncrease, MAX_SCALE);
//     scale.y = fminf(scale.y + *scaleIncrease, MAX_SCALE);
//     rectangle_setScale(rectangle, scale);
// }

// void scaleSmaller(va_list args) {
//     rectangle_s* rectangle = va_arg(args, rectangle_s*);
//     float* scaleDecrease = va_arg(args, float*);

//     vec2_s scale = rectangle_getScale(rectangle);
//     scale.x = fmaxf(scale.x - *scaleDecrease, MIN_SCALE);
//     scale.y = fmaxf(scale.y - *scaleDecrease, MIN_SCALE);
//     rectangle_setScale(rectangle, scale);
// }

// void doSomething()
// {
//     printf("YES\n");
// }


// void doSomething2()
// {
//     printf("NO\n");
// }


// int main(void) {

//     window_s* window = window_create(800, 600, "Game", false);
//     shader_s* shader = shader_create(window, "shaders/default_vert.glsl", "shaders/default_frag.glsl");

//     texture_s* texture = load_texture("assets/wall.jpg");
//     texture_s* texture2 = load_texture("assets/lava.png");

//     rectangle_s* rectangle = rectangle_create();
//     rectangle_setColor(rectangle, (vec4_s){1.0f, 0.0f, 0.0f, 1.0f});
//     rectangle_setSize(rectangle, (vec2_s){1.0f, 1.0f});
//     rectangle_setScale(rectangle, (vec2_s){50.0f, 50.0f});
//     rectangle_setPosition(rectangle, (vec2_s){(800/2) + 100, 600/2});
//     rectangle_setTexture(rectangle, texture);
//     rectangle_setTextureRect(rectangle, texture, (rect_float_s){0.0f, 0.0f, 512.0f, 512.0f});

//     const int NUM_RECTS = 25;
//     rectangle_s *rectangles[NUM_RECTS];
//     for (int i = 0; i < NUM_RECTS; i++) {
//         rectangles[i] = rectangle_create();
//         rectangle_setColor(rectangles[i], (vec4_s){0.0f, 1.0f, 0.0f, 1.0f});
//         rectangle_setSize(rectangles[i], (vec2_s){1.0f, 1.0f});
//         rectangle_setScale(rectangles[i], (vec2_s){50.0f, 50.0f});
//         if (i >= 9 && i <= 16) { 
//             static int j = 0;
//             rectangle_setPosition(rectangles[i], (vec2_s){(j * 110), 200.0f});
//             j++;
//         }
//         else if (i > 16) {
//             static int k = 0;
//             rectangle_setPosition(rectangles[i], (vec2_s){(k * 110), 400.0f});
//             k++;
//         }
//         else {
//             rectangle_setPosition(rectangles[i], (vec2_s){(i * 110), 0.0f});
//         }
//         rectangle_setTexture(rectangles[i], texture2);
//     }

//     float i = 0.0f;



//     int keyCombination1[] = {KEY_X, KEY_C, -1};  // Example: X and C keys pressed simultaneously
//     int keyCombination2[] = {KEY_A, KEY_S, -1};  // Example: A and S keys pressed simultaneously
//     int* key_combinations[] = {keyCombination1, keyCombination2};  // Array of key combinations
//     float debounceTimes[] = {0.05f, 0.05f};  // Debounce time for each combination
//     void (*callbacks[])(va_list) = {doSomething, doSomething2};

//     float scaleAmount = 1.0f;  // The scaling increment/decrement
//     float time = 0.05f;        // Debounce time
//     while (!window_shouldClose(window)) {
//         double deltatime = window_getDeltaTime();
//        // window_showFps();



//         // if (input_isKeyPressed(window, KEY_D)) {
//         //     rectangle_move(rectangle, (vec2_s){100.0f * deltatime, 0.0f});
//         // } if (input_isKeyPressed(window, KEY_A)) {
//         //     rectangle_move(rectangle, (vec2_s){-100.0f * deltatime, 0.0f});
//         // } if (input_isKeyPressed(window, KEY_W)) {
//         //     rectangle_move(rectangle, (vec2_s){0.0f, -100.0f * deltatime});
//         // } if (input_isKeyPressed(window, KEY_S)) {
//         //     rectangle_move(rectangle, (vec2_s){0.0f, 100.0f * deltatime});
//         // }

//     //    rectangle_handleInput(window, KEY_X, time, &scaleBigger, rectangle, &scaleAmount);
//     //    rectangle_handleInput(window, KEY_C, time, &scaleSmaller, rectangle, &scaleAmount);

//         // // Define the keys you want to handle
//         // int keys[] = {KEY_R, KEY_T}; // For example, the X and C keys
//         // // Define the debounce times for each key
//         // float debounceTimes[] = {1.0f, 1.0f}; // Both keys will have the same debounce time
//         // // Define the corresponding callbacks
//         // void CALLBACK_TYPE(doCallBacks) = {doSomething, doSomething}; // The corresponding callbacks for each key
//         // input_handleKeyCombinaison(window, keys, debounceTimes, doCallBacks, 2);


//             // Define the array of callback functions

//         // Call the function with the defined key combinations and callbacks
//         input_handleKeyCombinaison(window, key_combinations, debounceTimes, callbacks, 2);

//         // if (input_isKeyPressed(window, KEY_Q)) {
//         //     i += 50.0f * deltatime;
//         //     rectangle_setRotation(rectangle, i);
//         // } if (input_isKeyPressed(window, KEY_E)) {
//         //     i -= 50.0f * deltatime;
//         //     rectangle_setRotation(rectangle, i);
//         // }

//         // bool collisionDetected = false; // Flag to track if collision happens

//         // for (int i = 0; i < NUM_RECTS; i++) {
//         //     // Check if the rectangle collides with any of the rectangles
//         //     if (rectangle_checkCollisionRectangle(rectangle, rectangles[i])) {
//         //         if (!collisionDetected) {
//         //             rectangle_setColor(rectangle, (vec4_s){0.0f, 1.0f, 0.0f, 1.0f}); // Green if a collision happens
//         //             collisionDetected = true; // Flag indicating collision was detected
//         //         }
//         //     }
//         // }
//         // if (!collisionDetected) {
//         //     rectangle_setColor(rectangle, (vec4_s){1.0f, 0.0f, 0.0f, 1.0f});
//         // }

//         window_clear(0.1f, 0.2f, 0.3f, 1.0f);
    

//         rectangle_draw(window, rectangle, shader);
//         for (int i = 0; i < NUM_RECTS; i++) {
//             rectangle_draw(window, rectangles[i], shader);
//         }


//         window_display(window, GLFW_KEY_ESCAPE);
//     }
//     texture_delete(texture);
//     texture_delete(texture2);
//     rectangle_destroy(rectangle);
//     for (int i = 0; i < NUM_RECTS; i++)
//         free(rectangles[i]);
//     shader_delete(shader);
//     window_destroy(window);
//     return 0;
// }
// #pragma endregion COLLISION

// #pragma region DEBOUNCE
// void input(){
//     static int window;
//     static int laser;
//     static int ONCE;
//     static int key1Pressed = 0;
//     if (keyboard_isKeyPressed(window, KEY_1)) {
//         if (!key1Pressed) {
//             audio_playSound(laser, ONCE);
//             key1Pressed = 1;
//         }
//     } else {
//         key1Pressed = 0; // Reset when key is released
//     }
// }
// #pragma endregion DEBOUNCE


// #pragma region ANIMATION
// #include "../include/core/main.h"
// #include "../include/nuklear/nuklear_configs.h"
// #include "../include/nuklear/nuklear.h"
// #include "../include/nuklear/nuklear_glfw_gl3.h"
// #include "../include/Window/window.h"
// #include "../include/core/shader.h"
// #include "../include/core/vao.h"
// #include "../include/core/vbo.h"
// #include "../include/core/ebo.h"
// #include "../include/core/log.h"
// #include "../include/core/texture.h"
// #include "../include/Input/keyboard.h"
// #include "../include/Input/mouse.h"
// #include "../include/shapes/rectangle.h"
// #include "../include/audio/music.h"
// #include "../include/audio/sound.h"

// int main(void) {
//     window_s* window = window_create(800, 600, "Game", false);
//     shader_s* shader = shader_create(window, "shaders/default_vert.glsl", "shaders/default_frag.glsl");

//     texture_s* textureIdle = texture_load("assets/wizard/Idle.png");
//     texture_s* textureRun = texture_load("assets/wizard/Run.png");

//     // HITBOX
//     rectangle_s* playerHitbox = rectangle_create();
//     float hitboxScaleFactorWidth = 0.38f;
//     float hitboxScaleFactorHeight = 0.5f;
//     rectangle_setSize(playerHitbox, (vec2_s){(1386/6) * hitboxScaleFactorWidth, 190 * hitboxScaleFactorHeight});
//     rectangle_setColor(playerHitbox, (vec4_s){0.0f, 1.0f, 0.0f, 0.5f});

//     // Main player rectangle
//     rectangle_s* player = rectangle_create();
//     rectangle_setPosition(player, (vec2_s){window_getWidth(window)/2-100, window_getHeight(window)/2});
//     rectangle_setScale(player, (vec2_s){1.0f, 1.0f});
//     rectangle_setSize(player, (vec2_s){1386/6, 190});
//     rectangle_setTexture(player, textureIdle);
//     rectangle_setTextureRect(player, textureIdle, (rect_float_s){0, 0, 1386/6, 190});

//     // Wall object
//     rectangle_s* wall = rectangle_create();
//     rectangle_setPosition(wall, (vec2_s){window_getWidth(window)/2-200, window_getHeight(window)/2});
//     rectangle_setScale(wall, (vec2_s){1.0f, 1.0f});
//     rectangle_setSize(wall, (vec2_s){20.0f, 20.0f});
//     rectangle_setColor(wall, (vec4_s){1.0f, 0.0f, 0.0f, 1.0f});

//     // Animation variables
//     int frameWidthIdle = 1386 / 6;
//     int frameHeightIdle = 190;
//     int currentFrameIdle = 0;

//     int frameWidthRun = 1848 / 8;
//     int frameHeightRun = 190;
//     int currentFrameRun = 0;
//     bool isRunning = false;
    
//     rect_float_s rectRun = {0, 0, frameWidthRun, frameHeightRun};
//     rect_float_s frameRectIdle = {0, 0, frameWidthIdle, frameHeightIdle};

//     double frameTime = 0.08;
//     double elapsedTime = 0.0;
//     texture_s* currentTexture = textureIdle;

//     while (!window_shouldClose(window)) {
//         window_showFps();
//         double deltatime = window_getDeltaTime();
//         elapsedTime += deltatime;
//         float speed = 100.0f * deltatime;

//         // Movement and animation logic
//         bool moving = false;

//         if (keyboard_isKeyPressed(window, KEY_D)) {
//             rectangle_move(player, (vec2_s){speed, 0.0f});
//             moving = true;
//         }
//         if (keyboard_isKeyPressed(window, KEY_A)) {
//             rectangle_move(player, (vec2_s){-speed, 0.0f});
//             moving = true;
//         }

//         if (moving) {
//             if (!isRunning) {  // Only switch to running animation once
//                 isRunning = true;
//                 currentTexture = textureRun;
//                 currentFrameRun = 0;
//                 rectRun.left = 0.0f;
//             }
//         } else {
//             if (isRunning) {  // Only switch to idle animation once
//                 isRunning = false;
//                 currentTexture = textureIdle;
//                 currentFrameIdle = 0;
//                 frameRectIdle.left = 0.0f;
//             }
//         }

//         // Update hitbox position
//         vec2_s playerPos = rectangle_getPosition(player);
//         vec2_s playerSize = rectangle_getSize(player);
//         vec2_s hitboxSize = rectangle_getSize(playerHitbox);
//         rectangle_setPosition(playerHitbox, (vec2_s){
//             playerPos.x + (playerSize.x - hitboxSize.x) / 2, 
//             playerPos.y + (playerSize.y - hitboxSize.y) / 2
//         });

//         // Update animation frame
//         if (elapsedTime > frameTime) {
//             elapsedTime = 0.0;
//             if (isRunning) {
//                 currentFrameRun = (currentFrameRun + 1) % 8;
//                 rectRun.left = currentFrameRun * frameWidthRun;
//                 rectangle_setTextureRect(player, currentTexture, rectRun);
//             } else {
//                 currentFrameIdle = (currentFrameIdle + 1) % 6; // Should match the number of idle frames
//                 frameRectIdle.left = currentFrameIdle * frameWidthIdle;
//                 rectangle_setTextureRect(player, currentTexture, frameRectIdle);
//             }
//         }

//         // Collision detection
//         if (rectangle_checkCollisionRectangle(playerHitbox, wall)) {
//             printf("COLLISION DETECTED!\n");
//         }

//         // Render everything
//         window_clear(0.1f, 0.2f, 0.3f, 1.0f);
//         rectangle_draw(window, player, shader);
//         rectangle_draw(window, wall, shader);
//         rectangle_draw(window, playerHitbox, shader);  // Debug: Draw hitbox

//         window_display(window, GLFW_KEY_ESCAPE);
//     }

//     shader_delete(shader);
//     window_destroy(window);
//     return 0;
// }
// #pragma endregion ANIMATION

// /*

// CC = gcc
// CXX = g++
// EXE = bin/game
// LIBRARY = bin/libgame.a

// SRC_DIR = src
// BIN_DIR = bin
// OTHER_DIR = others
// GLAD_DIR = $(OTHER_DIR)/glad
// GLM_DIR = $(OTHER_DIR)/cglm/include
// STB_IMAGE_DIR = $(OTHER_DIR)/stb_image
// NUKLEAR_DIR = $(OTHER_DIR)/nuklear
// INCLUDE_DIR = include

// SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c')
// GLAD_FILE = $(GLAD_DIR)/glad.c
// STB_IMAGE_FILE = $(STB_IMAGE_DIR)/stb_image.c

// # Generate object file paths with the same directory structure as SRC_FILES
// OBJS = 	$(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES)) \
// 		$(BIN_DIR)/glad.o $(BIN_DIR)/stb_image.o

// OPENGL_LIBS = -ldl -lm -lX11 -lglfw -lm -lOpenGL -lGL -lpthread -lSDL2 -lSDL2_mixer -g
// INCLUDE = -I$(INCLUDE_DIR) -I$(OTHER_DIR) -I$(GLAD_DIR) -I$(GLM_DIR) -I$(STB_IMAGE_DIR) -I$(NUKLEAR_DIR)

// .PHONY: all clean re lib

// all: $(EXE)
// 	./$(EXE)

// $(EXE): $(LIBRARY)
// 	$(CC) -L$(BIN_DIR) -lgame -o $(EXE) $(OPENGL_LIBS)

// # Build the static library
// $(LIBRARY): $(OBJS)
// 	ar rcs $(LIBRARY) $(OBJS)

// # Rule to build object files in subdirectories
// $(BIN_DIR)/%.o: $(SRC_DIR)/%.c
// 	@mkdir -p $(dir $@)
// 	$(CC) $(INCLUDE) -c $< -o $@

// $(BIN_DIR)/glad.o: $(GLAD_FILE)
// 	@mkdir -p $(BIN_DIR)
// 	$(CC) $(INCLUDE) -c $< -o $@

// $(BIN_DIR)/stb_image.o: $(STB_IMAGE_FILE)
// 	@mkdir -p $(BIN_DIR)
// 	$(CC) $(INCLUDE) -c $< -o $@

// clean:
// 	rm -f $(EXE) $(LIBRARY) $(BIN_DIR)/*.o $(shell find $(BIN_DIR) -type f -name '*.o')

// re: clean all

// */