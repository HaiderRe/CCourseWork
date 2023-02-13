#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"

/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
struct {             // Structure declaration
  int x = 0;
  int y = 0;         // Member (int variable)   // Member (string variable)
} leftRect,rightRect, ball;
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    leftRect.x = 20;
    leftRect.y = 540;
    rightRect.x = 1900;
    rightRect.y = 540;
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    unsigned int counter_of_loops = 0;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    ball.x = static_cast<int>(GetScreenWidth() / 2); 
    ball.y = static_cast<int>(GetScreenHeight() / 2 );


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
            
        
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 		{
            ToggleFullscreen();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawCircle(ball.x, ball.y, 10, RAYWHITE);
            DrawRectangle(leftRect.x, leftRect.y, 4, 60, WHITE);
            DrawRectangle(rightRect.x, rightRect.y, 4, 60, WHITE);
            DrawFPS(10, 10);

        EndDrawing();
        counter_of_loops++;
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}