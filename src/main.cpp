#include "raylib.h"

static bool numberClicked(int num);

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Connect 4");
    SetTargetFPS(60);

    // Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_ONE))
            numberClicked(1);
        if (IsKeyDown(KEY_TWO))
            numberClicked(2);
        if (IsKeyDown(KEY_THREE))
            numberClicked(3);
        if (IsKeyDown(KEY_FOUR))
            numberClicked(4);
        //----------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(SKYBLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

static bool numberClicked(int num)
{
}