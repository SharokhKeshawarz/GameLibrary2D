#include <SFML/Graphics.h>
#include <SFML/System.h>

int main()
{
    // Create a window
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Sprite Animation", sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 240);
    if (!window)
        return 1;

    // Load the sprite sheet textures
    sfTexture* textureIdle = sfTexture_createFromFile("assets/wizard/Idle.png", NULL);
    if (!textureIdle)
        return 1;

    sfTexture* textureRun = sfTexture_createFromFile("assets/wizard/Run.png", NULL);
    if (!textureRun)
        return 1;

    sfTexture* textureAttack = sfTexture_createFromFile("assets/wizard/Attack1.png", NULL);
    if (!textureAttack)
        return 1;

    sfTexture* textureAttack2 = sfTexture_createFromFile("assets/wizard/Attack2.png", NULL);
    if (!textureAttack)
        return 1;
    
    sfTexture* textureJump = sfTexture_createFromFile("assets/wizard/Jump.png", NULL);
    if (!textureJump)
        return 1;
    sfTexture* textureFall = sfTexture_createFromFile("assets/wizard/Fall.png", NULL);
    if (!textureFall)
        return 1;
    // Create a sprite and set the initial texture (Idle)
    sfSprite* sprite = sfSprite_create();
    sfSprite_setPosition(sprite, (sfVector2f){100.0f, 100.0f});
    sfSprite_setTexture(sprite, textureIdle, sfTrue);
    sfSprite_setOrigin(sprite, (sfVector2f){(1848/8) / 2.0f, 190 / 2.0f});

    // Define the animation frame size and other variables for each animation
    /* IDLE */
    int frameWidthIdle = 1386 / 6;   // Width of a single frame (Idle)
    int frameHeightIdle = 190;      // Height of a single frame (Idle)
    int currentFrameIdle = 0;       // Index of the current frame (Idle)
    sfIntRect frameRectIdle = {0, 0, frameWidthIdle, frameHeightIdle}; // Starting frame (Idle)

    /* RUN */
    int frameWidthRun = 1848 / 8;   // Width of a single frame (Run)
    int frameHeightRun = 190;      // Height of a single frame (Run)
    int currentFrameRun = 0;       // Index of the current frame (Run)
    sfIntRect frameRectRun = {0, 0, frameWidthRun, frameHeightRun}; // Starting frame (Run)

    /* ATTACK */
    int frameWidthAttack = 1848 / 8; // Width of a single frame (Attack)
    int frameHeightAttack = 190;    // Height of a single frame (Attack)
    int currentFrameAttack = 0;     // Index of the current frame (Attack)
    sfIntRect frameRectAttack = {0, 0, frameWidthAttack, frameHeightAttack}; // Starting frame (Attack)

    /* JUMP */
    int frameWidthJump = 462 / 2;
    int frameHeightJump = 190;
    int currentFrameJump = 0;
    sfIntRect frameRectJump = {0, 0, frameWidthJump, frameHeightJump};

    /* FALLS */
    int frameWidthFall = 462 / 2; // Width of a single frame (Falling)
    int frameHeightFall = 190;    // Height of a single frame (Falling)
    int currentFrameFall = 0;     // Index of the current frame (Falling)
    sfIntRect frameRectFall = {0, 0, frameWidthFall, frameHeightFall}; // Starting frame (Falling)

    /* TIMES */
    sfClock* clock = sfClock_create();  // Clock to handle animation timing
    float frameTime = 0.08f; // Time per frame (in seconds)
    float elapsedTime = 0.0f;

    // Track the current animation state
    int isRunning = 0;      // 0 = Idle, 1 = Run, 2 = Jump, 3 = Fall
    int isJumping = 0;
    int isAttacking = 0;    // 1 = Attacking
    int isFalling = 0;
    int fallFinished = 1;
    int jumpFinished = 1;
    int attackFinished = 1; // 1 = Animation is done or not playing
    

    int whichAttack = 0;
    sfTexture* currentTexture = textureIdle;

    // Apply the initial texture rectangle (Idle)
    sfSprite_setTextureRect(sprite, frameRectIdle);

    // Main game loop
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // Update elapsed time
        sfTime currentTime = sfClock_getElapsedTime(clock);
        float deltaTime = sfTime_asSeconds(currentTime);
        elapsedTime += deltaTime;
        float speed = 200.0f * deltaTime;

        // Attack animation logic
        if (sfKeyboard_isKeyPressed(sfKeyE) && attackFinished) {
            // Trigger attack animation
            isAttacking = 1;
            attackFinished = 0;
            currentFrameAttack = 0; // Reset the attack frame index
            frameRectAttack.left = 0;
            whichAttack = 1;
            sfSprite_setTexture(sprite, textureAttack, sfTrue); // Switch to Attack texture
            sfSprite_setTextureRect(sprite, frameRectAttack);   // Set the first Attack frame
        }
        // Attack animation logic 2
        if (sfKeyboard_isKeyPressed(sfKeyA) && attackFinished) {
            // Trigger attack animation
            isAttacking = 1;
            attackFinished = 0;
            currentFrameAttack = 0; // Reset the attack frame index
            frameRectAttack.left = 0;
            whichAttack = 2;
            sfSprite_setTexture(sprite, textureAttack2, sfTrue); // Switch to Attack texture
            sfSprite_setTextureRect(sprite, frameRectAttack);   // Set the first Attack frame
        }

        // Jump animation logic
        if (sfKeyboard_isKeyPressed(sfKeySpace)) {
            isJumping = 1;
            jumpFinished = 0;
            currentFrameJump = 0;
            frameRectJump.left = 0;
            sfSprite_setTexture(sprite, textureJump, sfTrue);
            sfSprite_setTextureRect(sprite, frameRectJump);
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)) {
            isFalling = 1;
            fallFinished = 0;
            currentFrameFall = 0;
            frameRectFall.left = 0;
            sfSprite_setTexture(sprite, textureFall, sfTrue);
            sfSprite_setTextureRect(sprite, frameRectFall);
        }
        // Handle attack animation when active
        if (isAttacking) {
            if (elapsedTime > frameTime) {
                elapsedTime = 0.0f;
                currentFrameAttack++;

                // Check if attack animation is complete
                if (currentFrameAttack >= 8) {
                    isAttacking = 0;
                    attackFinished = 1; // Mark attack as finished
                    sfSprite_setTexture(sprite, textureIdle, sfTrue); // Return to Idle texture
                    sfSprite_setTextureRect(sprite, frameRectIdle);   // Reset to Idle frame
                } else {
                    // Update the attack frame rectangle
                    frameRectAttack.left = currentFrameAttack * frameWidthAttack;
                    sfSprite_setTextureRect(sprite, frameRectAttack);
                }
            }
        }
    
        // Running Logic
        if (!isJumping && !isAttacking && !isFalling) {
            if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyQ)) {
                if (!isRunning) {
                    sfSprite_setTexture(sprite, textureRun, sfTrue); // Switch to Run texture
                    sfSprite_setTextureRect(sprite, frameRectRun);   // Set the first Run frame
                    isRunning = 1;
                }

                // Update Run animation
                if (elapsedTime > frameTime) {
                    elapsedTime = 0.0f;
                    currentFrameRun = (currentFrameRun + 1) % 8; // Loop through the 8 frames of Run
                    frameRectRun.left = currentFrameRun * frameWidthRun; // Move to the next frame
                    sfSprite_setTextureRect(sprite, frameRectRun);
                }
            } else {
                // No movement, switch to Idle
                if (isRunning) {
                    sfSprite_setTexture(sprite, textureIdle, sfTrue); // Switch back to Idle texture
                    sfSprite_setTextureRect(sprite, frameRectIdle);   // Set the first Idle frame
                    isRunning = 0;
                }

                // Update Idle animation
                if (elapsedTime > frameTime) {
                    elapsedTime = 0.0f;
                    currentFrameIdle = (currentFrameIdle + 1) % 6; // Loop through the 6 frames of Idle
                    frameRectIdle.left = currentFrameIdle * frameWidthIdle; // Move to the next frame
                    sfSprite_setTextureRect(sprite, frameRectIdle);
                }
            }
        }

        // Jump Animation Logic
        if (isJumping && !isAttacking && !isFalling) {
            if (elapsedTime > frameTime) {
                elapsedTime = 0.0f;
                currentFrameJump++;
                if (currentFrameJump >= 2) { // Jump animation ends
                    isJumping = 0;
                    jumpFinished = 1;

                    // Check if still running after jump
                    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyQ)) {
                        isRunning = 1;
                        sfSprite_setTexture(sprite, textureRun, sfTrue); // Switch to Run texture
                        sfSprite_setTextureRect(sprite, frameRectRun);   // Start Run animation
                    } else {
                        // If not running, switch to Idle
                        sfSprite_setTexture(sprite, textureIdle, sfTrue);
                        sfSprite_setTextureRect(sprite, frameRectIdle);
                    }
                } else {
                    // Continue jump animation
                    frameRectJump.left = currentFrameJump * frameWidthJump;
                    sfSprite_setTextureRect(sprite, frameRectJump);
                }
            }
        }
        // Handle falling animation
        if (isFalling && !isAttacking && !isJumping) {
            if (elapsedTime > frameTime) {
                elapsedTime = 0.0f;
                currentFrameFall++;
                if (currentFrameFall >= 2) {
                    isFalling = 0; // Fall animation finishes
                    fallFinished = 1;

                    // Check if still running after jump
                    if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyQ)) {
                        isRunning = 1;
                        sfSprite_setTexture(sprite, textureRun, sfTrue); // Switch to Run texture
                        sfSprite_setTextureRect(sprite, frameRectRun);   // Start Run animation
                    } else {
                        // If not running, switch to Idle
                        sfSprite_setTexture(sprite, textureIdle, sfTrue);
                        sfSprite_setTextureRect(sprite, frameRectIdle);
                    }
                    sfSprite_setTexture(sprite, textureIdle, sfTrue); // Switch back to Idle texture
                    sfSprite_setTextureRect(sprite, frameRectIdle);   // Set the first Idle frame
                } else {
                    // Update the falling frame rectangle
                    frameRectFall.left = currentFrameFall * frameWidthFall;
                    sfSprite_setTextureRect(sprite, frameRectFall);
                }
            }
        }


        // Right movement (D key)
        if (isRunning && sfKeyboard_isKeyPressed(sfKeyD)) {
            float height = 0.0f;

            // Handle jump (going up) or fall (going down), but not both
            if (isJumping && sfKeyboard_isKeyPressed(sfKeySpace)) {
                height = -100.0f * deltaTime; // Jumping upwards
            } else if (isFalling && sfKeyboard_isKeyPressed(sfKeyS)) {
                height = 100.0f * deltaTime; // Falling downwards
            }

            // Move the sprite horizontally to the right and apply the vertical movement
            sfSprite_setScale(sprite, (sfVector2f){1.0f, 1.0f});
            sfSprite_move(sprite, (sfVector2f){speed, height});
        }

        // Left movement (Q key)
        if (isRunning && sfKeyboard_isKeyPressed(sfKeyQ)) {
            float height = 0.0f;

            // Handle jump (going up) or fall (going down), but not both
            if (isJumping && sfKeyboard_isKeyPressed(sfKeySpace)) {
                height = -100.0f * deltaTime; // Jumping upwards
            } else if (isFalling && sfKeyboard_isKeyPressed(sfKeyS)) {
                height = 100.0f * deltaTime; // Falling downwards
            }

            // Move the sprite horizontally to the left and apply the vertical movement
            sfSprite_setScale(sprite, (sfVector2f){-1.0f, 1.0f});
            sfSprite_move(sprite, (sfVector2f){-speed, height});
        }

        // If not running, allow jumping and falling independently
        if (!isRunning) {
            // Handle Jump and Fall movements when the player is not running
            if (sfKeyboard_isKeyPressed(sfKeySpace) && !isJumping && !isFalling) {
                // Jumping action
                isJumping = 1;
                jumpFinished = 0;
                currentFrameJump = 0;
                frameRectJump.left = 0;
                sfSprite_setTexture(sprite, textureJump, sfTrue);
                sfSprite_setTextureRect(sprite, frameRectJump);
            }

            if (sfKeyboard_isKeyPressed(sfKeyS) && !isFalling && !isJumping) {
                // Falling action
                isFalling = 1;
                fallFinished = 0;
                currentFrameFall = 0;
                frameRectFall.left = 0;
                sfSprite_setTexture(sprite, textureFall, sfTrue);
                sfSprite_setTextureRect(sprite, frameRectFall);
            }

            // Apply the vertical movement (jump or fall) when the player is not running
            if (isJumping && sfKeyboard_isKeyPressed(sfKeySpace)) {
                sfSprite_move(sprite, (sfVector2f){0.0f, -100.0f * deltaTime}); // Move up (jump)
            }

            if (isFalling && sfKeyboard_isKeyPressed(sfKeyS)) {
                sfSprite_move(sprite, (sfVector2f){0.0f, 100.0f * deltaTime}); // Move down (fall)
            }
        }

        sfClock_restart(clock); // Restart the clock for the next frame

        // Clear the window
        sfRenderWindow_clear(window, sfBlack);

        // Draw the sprite
        sfRenderWindow_drawSprite(window, sprite, NULL);

        // Display the window contents
        sfRenderWindow_display(window);

        // Close the window when Escape is pressed
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window);
    }

    // Cleanup
    sfSprite_destroy(sprite);
    sfTexture_destroy(textureIdle);
    sfTexture_destroy(textureRun);
    sfTexture_destroy(textureAttack);
    sfClock_destroy(clock);
    sfRenderWindow_destroy(window);

    return 0;
}
