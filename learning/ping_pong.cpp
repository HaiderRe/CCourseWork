#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"
#include <vector>

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


struct texture_struct{
    Texture2D t_texture;
    float x;
    float y;
    float width;
    float height;
    int scale = 1;
    int frame = -1;
    int iteration = 1;
    float frame_timer = 0;
    float b_x;
    float b_y;
};
struct objects{             // Structure declaration
  int x = 0;
  int y = 0;
  int p_counter = 1;   // p = powerup
  bool is_parrying = false;
  int parry_cool_down = 0;  
  bool has_texture = false;  
  texture_struct c_texture;
} leftRect,rightRect, ball;
void shoot_gun();
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    std::vector<texture_struct> vec_textures;
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
                leftRect.p_counter = 1;
                rightRect.p_counter = 1;
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
       shoot_gun();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            if(leftRect.c_texture.frame > -1){
                DrawTexturePro(leftRect.c_texture.t_texture,Rectangle{leftRect.c_texture.x, leftRect.c_texture.y, leftRect.c_texture.width, leftRect.c_texture.height}, Rectangle{leftRect.c_texture.b_x, leftRect.c_texture.b_y, 8, 8},Vector2{leftRect.c_texture.b_x + 4, leftRect.c_texture.b_y + 4}, 0.0f ,RAYWHITE);
            }
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
        if(ball.y > leftRect.y){
            ball_speedy = abs(ball_speedy) * -1;
        }
        else{
            ball_speedy = abs(ball_speedy);
        }
    }
    else if(CheckCollisionCircleRec(Vector2{float(ball.x), float(ball.y)}, 10 , Rectangle{float(rightRect.x),float(rightRect.y), 4, 60 })){
        ball_speedx *= -1;
        if(ball.y  > rightRect.y ){
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
void shoot_gun(){
   // texture_struct arr [2];
    if(IsKeyPressed(KEY_F) && leftRect.p_counter > 0){
        struct texture_struct bullet;
        bullet.t_texture = LoadTexture("./asset/Air_I_16x16.png");
        bullet.width = float(16);
        bullet.height = bullet.width;
        bullet.frame = 0;
        leftRect.p_counter += -1;
        leftRect.c_texture = bullet;
        leftRect.has_texture = true;
        leftRect.c_texture.b_y = float(leftRect.y);
        std::cout << "spawned" << std::endl;
    }
    if(IsKeyPressed(KEY_SPACE) && rightRect.p_counter > 0){
        struct texture_struct bullet_Right;
        bullet_Right.t_texture = LoadTexture("./asset/Air_I_16x16.png");
        bullet_Right.width = float(16);
        bullet_Right.height = bullet_Right.width;
        bullet_Right.frame = 0; 
        rightRect.p_counter += -1;
        rightRect.c_texture = bullet_Right;
        rightRect.has_texture = true;
        rightRect.c_texture.b_y = float(rightRect.y);
    }
    if(leftRect.c_texture.frame > -1){
        //arr[0] = leftRect.c_texture;
        leftRect.c_texture.b_x += 4;
        leftRect.c_texture.frame_timer += GetFrameTime();
        if(leftRect.c_texture.frame_timer >= float(0.2) ){
            std::cout << "frame incremented" << std::endl;
            leftRect.c_texture.frame += 1;
            leftRect.c_texture.x += 16;
            if(leftRect.c_texture.frame == 4){
                leftRect.c_texture.x = 0;
                leftRect.c_texture.y += 16;
            }
            leftRect.c_texture.frame_timer = float(0);
            if(leftRect.c_texture.frame > 6){
                leftRect.c_texture.frame = 1;
            }
        }
        // std::cout << "leftrect frame > -1" << std::endl;
    }
    if(rightRect.c_texture.frame > -1){
       // arr[1] = rightRect.c_texture;
        rightRect.c_texture.b_x += -4;
        rightRect.c_texture.frame_timer += GetFrameTime();
        if(rightRect.c_texture.frame_timer >= float(0.2) ){
            std::cout << "frame incremented" << std::endl;
            rightRect.c_texture.frame += 1;
            rightRect.c_texture.x += 16;
            if(rightRect.c_texture.frame == 4){
                rightRect.c_texture.x = 0;
                rightRect.c_texture.y += 16;
            }
            rightRect.c_texture.frame_timer = float(0);
            if(rightRect.c_texture.frame > 6){
                rightRect.c_texture.frame = 1;
            }
        }
    }
}