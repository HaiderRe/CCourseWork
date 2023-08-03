// Note for self 
// Instead of whatever we do right now for xml parseing, combine tilesets into one 
// so one image for one tilemap 
// Then have image as same name as tilemap 
// Then get image divide into sections by tile width and height  
// And then pray 
// std::cout << " pass bullshit" << std::endl;
  //      std::cout << "Size of xmlTileIDs: " << xmlTileIDs.size() << std::endl;

      /*  for(int aB = 0; aB < xmlTileIDs.size(); aB++){
          for(int aC = 0; aC < xmlTileIDs[0].size(); aC++){
//            std::cout<< "in" << std::endl;
            std::cout<< std::to_string(xmlTileIDs[aB][aC]) << std::endl;
          }
        }
        */
       // Draw the tilemap and tileset
                // xmlFile.draw_xml_file();
                 // replace 0 with the index of the tileset you want to draw
#ifndef main_game
#define main_game
#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"
#include <vector>
#include "include/camera.hpp"
#include "include/xml_parser.hpp"
#include "include/game_renderer.hpp"
#include "include/player_objects.hpp"
#include "include/mouseHandler.hpp"

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
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "Raylib Test");
    InitAudioDevice(); // For sound
   
    int y_size = default_map.y_size;
    int y = 0;
    int x  = 0; 
    int oldx = 0; 
    int oldy = 0;
    game_renderer_h_1::game_renderer gameRenderer;
    player_objects::player nPlayer;
    camera_h::camera_class camera(nPlayer);
    mouseHandler::mouseHandlerClass mouseHandlerObject;
    int shouldClose = 0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    default_map.set_width_height_of_arr(256,256);
    default_map.set_width_height(32, 32);

    // Create an instance of file_to_read and read the XML file
  // Create an instance of file_to_read and read the XML file
 my_xml_parser::file_to_read xmlFile("include/testing_functionalilty_of_parser.xml");
 xmlFile.set_map_texture();
 xmlFile.set_column();
 //xmlFile.make_tileset_file();
 SetExitKey(KEY_NULL);

  
    // Main game loop
    while (!WindowShouldClose() && shouldClose != 1)    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        // Update
        gameRenderer.update();
        gameRenderer.skillUpdate(nPlayer.skillManagerObject.skillSlotsObject.currentSkills, &nPlayer.skillManagerObject.skillSlotsObject.equippedSkills);
        bool isPaused;
        isPaused =  gameRenderer.getGameIsPaused();
        if(isPaused == false){
         nPlayer.update(xmlFile.getCollisionTileIDs());
         camera.update();
        }
        else{
          shouldClose = gameRenderer.menuLogic();
        }
 
        default_map.arr_tiles[0*y_size+2171].is_black = true;
        mouseHandlerObject.update();
        
     
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        std::vector<std::vector<int>> xmlTileIDs = xmlFile.get_tileIDs();
       
         BeginDrawing();

            ClearBackground(WHITE);
            
            DrawFPS(10, 10);  // Draw current FPS
            nPlayer.drawOffCamera();
            if(isPaused == false){
            BeginMode2D(camera.cam);
                xmlFile.new_draw_tilemap();
               // default_map.draw();
                nPlayer.draw();

                

            EndMode2D();
            }
            else{
              if(gameRenderer.whichPause == 4){
                BeginMode2D(camera.cam);
                // Apply custom shader to screen using custom code no get shader but using pixel transformations
                
                xmlFile.new_draw_tilemap();
                nPlayer.draw();

                EndMode2D();
              }
              gameRenderer.drawPauseMenu();
              
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete[] default_map.arr_tiles;
    UnloadTexture(xmlFile.get_map_texture().texture);
    for(int k = 0; k < nPlayer.playerAnims.animations.size(); k++){
      UnloadTexture(nPlayer.playerAnims.animations[k].texture1);
    }
    // UnloadTexture(nPlayer.playerAnims.animations[0].texture1);
    for(int j = 0; j < gameRenderer.getTexturesToBeDeAllocated().size(); j++){
      UnloadTexture(gameRenderer.getTexturesToBeDeAllocated()[j]);
    }
    for(int l = 0; l < nPlayer.skillManagerObject.skills.size(); l++){
      for(int p = 0; p < nPlayer.skillManagerObject.skills[l].textures.size(); p++){
      UnloadTexture(nPlayer.skillManagerObject.skills[l].textures[p]);
      }
    UnloadTexture(nPlayer.skillManagerObject.skills[l].skillIcon);
    }
    CloseAudioDevice(); // Close sound device
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
#endif