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
void should_move();
void ball_speed(int &ballspeedx, int &ballspeedy);
bool check_scored(unsigned int &l_score, unsigned int &r_score);
struct objects{             // Structure declaration
  int x = 0;
  int y = 0;      // Member (int variable)   // Member (string variable)
} leftRect,rightRect, ball;
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    leftRect.x = 20;
    leftRect.y = 540;
    rightRect.x = 1900;
    rightRect.y = 540;
    unsigned int left_rect_score = 0;
    unsigned int right_rect_score = 0;
    bool score_timer = false;
    unsigned int counter_of_time = 1;
    int ball_speedx = GetRandomValue(5, 8);
    int ball_speedy = GetRandomValue(4, 7);
    int tmp = GetRandomValue(0,3);
    if(tmp == 0){
        ball_speedx *= -1;
    }
    else if(tmp == 1){
        ball_speedx *= -1;
        ball_speedy *= -1;
    }
    else if(tmp == 3){
        ball_speedy *= -1;
    }
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    unsigned int counter_of_loops = 0;
    InitWindow(screenWidth, screenHeight, "Pong");
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
        should_move();
        if(!score_timer){
        ball_speed(ball_speedx, ball_speedy);
        }
        else{
            counter_of_time = counter_of_time + 1;
            if(counter_of_time % 180 == 0){
                counter_of_time = 1;
                ball_speedx = GetRandomValue(5, 8);
                ball_speedy = GetRandomValue(4, 7);
                tmp = GetRandomValue(0,3);
                if(tmp == 0){
                    ball_speedx *= -1;
                }
                else if(tmp == 1){
                    ball_speedx *= -1;
                    ball_speedy *= -1;
                }
                else if(tmp == 3){
                    ball_speedy *= -1;
                }
                
                score_timer = false;
            }
        }
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 		{
            ToggleFullscreen();
        }
        if(counter_of_loops % 30 == 0){
            ball_speedx *= 1.04;
            ball_speedy *= 1.02;
        }
       if(!score_timer){
       score_timer = check_scored(left_rect_score, right_rect_score);
       }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawCircle(ball.x, ball.y, 10, RAYWHITE);
            DrawRectangle(leftRect.x, leftRect.y, 4, 60, WHITE);
            DrawRectangle(rightRect.x, rightRect.y, 4, 60, WHITE);
            DrawRectangle(960,0, 4, 1080, WHITE);
            DrawText(TextFormat(" %i", left_rect_score),490, 108, 32, WHITE);
            DrawText(TextFormat(" %i", right_rect_score),1459, 108, 32, WHITE);
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
void should_move(){
    if(IsKeyDown(KEY_W)){
        leftRect.y = leftRect.y - 10;
    }
    else if(IsKeyDown(KEY_S)){
        leftRect.y = leftRect.y + 10;
    }
    if(IsKeyDown(KEY_DOWN)){
        rightRect.y = rightRect.y + 10;
    }
    else if(IsKeyDown(KEY_UP)){
        rightRect.y = rightRect.y - 10;
    }
    if(leftRect.y < 0){
        leftRect.y = 0;
    }
    else if(leftRect.y > (GetScreenHeight() - 60)){
        leftRect.y = GetScreenHeight() - 60;
    }
    if(rightRect.y < 0){
        rightRect.y = 0;
    }
    else if(rightRect.y > GetScreenHeight() - 60){
        rightRect.y = GetScreenHeight() - 60;
    }
}
void ball_speed(int &ball_speedx, int &ball_speedy){
    ball.y = ball.y + ball_speedy;
    if(ball.y < 0 || ball.y > GetScreenHeight()){
        ball_speedy *= -1;
    }
    ball.x = ball.x + ball_speedx; 
    if(CheckCollisionCircleRec(Vector2{float(ball.x), float(ball.y)}, 10 , Rectangle{float(leftRect.x),float(leftRect.y), 4, 60 })){
        ball_speedx *= -1;
        if(ball.y > leftRect.y + 5){
            ball_speedy = abs(ball_speedy) * -1;
        }
        else{
            ball_speedy = abs(ball_speedy);
        }
    }
    else if(CheckCollisionCircleRec(Vector2{float(ball.x), float(ball.y)}, 10 , Rectangle{float(rightRect.x),float(rightRect.y), 4, 60 })){
        ball_speedx *= -1;
        if(ball.y > rightRect.y + 5){
            ball_speedy = abs(ball_speedy) * -1;
        }
        else{
            ball_speedy = abs(ball_speedy);
        }
    }
}
bool check_scored(unsigned int &l_score, unsigned int &r_score){
    if(ball.x < 0){
        l_score = l_score + 1;
        ball.x = 964;
        ball.y = 540;
        return true;
    }
    else if(ball.x > 1920){
        r_score = r_score + 1;
        ball.x = 964;
        ball.y = 540;
        return true;
    }
    return false;
}