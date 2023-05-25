#ifndef main_game
#define main_game
#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"
#include <vector>
#include "include/xml_parser.hpp"
#include "include/game_renderer.hpp"
#include "include/player_objects.hpp"
#include "include/enemy_objects.hpp"
#include "include/tile_map.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
using namespace tilemap_ns;
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    tilemap default_map; 
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "Raylib Test");
    Camera2D cam = {0};
    cam.zoom = 1.0f;
    cam.target = Vector2{ 00.0f, 00.0f };
    cam.offset = Vector2{ screenWidth/2.0f, screenHeight/2.0f };
    cam.rotation = 0.0f;
    int y_size = default_map.y_size;
    int y = 0;
    int x  = 0;
    int oldx = 0; 
    int oldy = 0;
    game_renderer_h_1::game_renderer gameRenderer;
    player_objects::player nPlayer;
    cam.target = nPlayer.destRecPos;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    default_map.set_width_height_of_arr(256,256);
    default_map.set_width_height(32, 32);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        // Update
        
      if(IsKeyDown(KEY_RIGHT) ) {
        nPlayer.destRecPos.x += 2.00f;
        }
        else if(IsKeyDown(KEY_LEFT)){
            
        nPlayer.destRecPos.x += -2.00f;
        }
        if(IsKeyDown(KEY_DOWN)){
      
        nPlayer.destRecPos.y += 2.00f;
        }
        else if(IsKeyDown(KEY_UP)){
        nPlayer.destRecPos.y += -2.00f;
        }
        if(IsKeyPressed(KEY_SPACE)){
            std::cout << "x " + std::to_string(cam.target.x) + " y " + std::to_string(cam.target.y) << std::endl;
        } 
        if(x > 63){
            x = 0; 
            y = y +  1;
        } 
     //  default_map.arr_tiles[oldx*y_size+oldy].is_black = false;
        default_map.arr_tiles[0*y_size+2171].is_black = true;
      //  oldx = x;
      //  oldy = y; 
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);
           

           BeginMode2D(cam);
            default_map.draw();
            nPlayer.draw();
          EndMode2D();
          

            
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete[] default_map.arr_tiles;
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
#endif