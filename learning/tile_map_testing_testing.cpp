// Note for self 
// Instead of whatever we do right now for xml parseing, combine tilesets into one 
// so one image for one tilemap 
// Then have image as same name as tilemap 
// Then get image divide into sections by tile width and height  
// And then pray 
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
//#include "include/enemy_objects.hpp"
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

    // Create an instance of file_to_read and read the XML file
  // Create an instance of file_to_read and read the XML file
 my_xml_parser::file_to_read xmlFile("include/testing_functionalilty_of_parser.xml");
 xmlFile.set_map_texture();
 //xmlFile.make_tileset_file();

  
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        // Update
        nPlayer.update();
 
     //  default_map.arr_tiles[oldx*y_size+oldy].is_black = false;
        default_map.arr_tiles[0*y_size+2171].is_black = true;
        
      //  oldx = x;
      //  oldy = y; 
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        std::vector<std::vector<int>> xmlTileIDs = xmlFile.get_tileIDs();
        std::cout << " pass bullshit" << std::endl;
  //      std::cout << "Size of xmlTileIDs: " << xmlTileIDs.size() << std::endl;

      /*  for(int aB = 0; aB < xmlTileIDs.size(); aB++){
          for(int aC = 0; aC < xmlTileIDs[0].size(); aC++){
//            std::cout<< "in" << std::endl;
            std::cout<< std::to_string(xmlTileIDs[aB][aC]) << std::endl;
          }
        }
        */
         BeginDrawing();

            ClearBackground(RAYWHITE);
              xmlFile.new_draw_tilemap();
            DrawFPS(10, 10);  // Draw current FPS
            BeginMode2D(cam);
               // default_map.draw();
                nPlayer.draw();
                // Draw the tilemap and tileset
                // xmlFile.draw_xml_file();
                 // replace 0 with the index of the tileset you want to draw

            EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete[] default_map.arr_tiles;
    UnloadTexture(xmlFile.get_map_texture().texture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
#endif