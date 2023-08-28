// Note for self 
// Instead of whatever we do right now for xml parseing, combine tilesets into one 
// so one image for one tilemap 
// Then have image as same name as tilemap 
// Then get image divide into sections by tile width and height  
// And then pray 
// std::cout << " pass " << std::endl;
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
#include "include/enemyObjects.hpp"
//#include "include/aStar.hpp"
//#include "include/enemy_objects.hpp"
#include "include/tile_map.hpp"
#include "include/sound.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
using namespace tilemap_ns;
enum currentMap {
    water_map,
    default_map,
    test_map
};
Vector2 chooseValidPos(std::vector<std::vector<int>> collisionTileIDs, bool ignoreFirstRow){
  Vector2 validPos = {0.00f, 0.00f};
  int rowX = 0;
  for(int i = 1; i < 64; i++){
    for(int j = 0; j < 64; j++){
      if(collisionTileIDs[i][j] == 0){
        rowX++;
        if(rowX < 10){
          continue;
        }
        validPos.x = i * 16;
        validPos.y = j * 16;
        return validPos;
      }
    }
  }
  std::clog << "no valid pos found" << std::endl;
  return validPos;
}
Vector2 chooseValidPos(std::vector<std::vector<int>> collisionTileIDs){
  Vector2 validPos = {0.00f, 0.00f};
  for(int i = 1; i < 64; i++){
    for(int j = 0; j < 64; j++){
      if(collisionTileIDs[i][j] == 0){
        validPos.x = i * 16;
        validPos.y = j * 16;
        return validPos;
      }
    }
  }
  std::clog << "no valid pos found" << std::endl;
  return validPos;
}
Vector2 chooseValidPosRandom(std::vector<std::vector<int>> collisionTileIDs){
  Vector2 validPos = {0.00f, 0.00f};
  SetRandomSeed(GetTime());
  int amountOfIter = 0;
  while(true){
    int randX = GetRandomValue(0, 63);
    int randY = GetRandomValue(0, 63);
    if(collisionTileIDs[randX][randY] == 0){
      validPos.x = randX * 16;
      validPos.y = randY * 16;
      return validPos;
    }
    amountOfIter = amountOfIter + 1;
    if(amountOfIter > 1000){ // Just in case it gets stuck in a loop
      return chooseValidPos(collisionTileIDs);
    }
  }
    
  
  std::clog << "no valid pos found" << std::endl;
  return validPos;
}
void spawnNShootingEnemies(int amouunt, enemyObjects_NS::enemyManager& theEnemyManager, std::vector<std::vector<int>> collisionTileIDs, player_objects::player& nPlayer){
  for(int i = 0; i < amouunt; i++){
    theEnemyManager.spawnShootingEnemy(chooseValidPos(collisionTileIDs), "fireMan.png", collisionTileIDs);
    theEnemyManager.smartPtrEnemies[i]->thePlayer = &nPlayer;
  }
}
void spawnNSlimeEnemies(int amount, enemyObjects_NS::enemyManager& theEnemyManager, std::vector<std::vector<int>> collisionTileIDs, player_objects::player& nPlayer){
  for(int i = 0; i < amount; i++){
    theEnemyManager.spawnSlimeEnemy(chooseValidPosRandom(collisionTileIDs), "blueSlime.png", collisionTileIDs);
    theEnemyManager.smartPtrEnemies[i]->thePlayer = &nPlayer;
  }
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
   tilemap default_map; 
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(screenWidth, screenHeight, "Game");
    InitAudioDevice(); // For sound
    int y_size = default_map.y_size;
    int y = 0;
    int x  = 0; 
    int oldx = 0; 
    int oldy = 0;
    SoundManager& manager = SoundManager::getInstance();
    game_renderer_h_1::game_renderer gameRenderer;
    player_objects::player nPlayer;
    camera_h::camera_class camera(nPlayer);
    mouseHandler::mouseHandlerClass mouseHandlerObject;
    int shouldClose = 0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    default_map.set_width_height_of_arr(256,256);
    default_map.set_width_height(32, 32);
    enemyObjects_NS::enemyManager theEnemyManager;
    //theEnemyManager.spawnEnemy(Vector2{100,100});
  //  theEnemyManager.enemies[0].thePlayer = &nPlayer;

    // Create an instance of file_to_read and read the XML file
  // Create an instance of file_to_read and read the XML file
  /// my_xml_parser::file_to_read xmlFile("include/testing_functionalilty_of_parser.xml");
   my_xml_parser::file_to_read xmlFile("include/water_tilemap.xml"); // Water_map
   currentMap aCurrentMap = water_map;
   
 xmlFile.set_map_texture();
 xmlFile.set_column();
 //xmlFile.make_tileset_file();
 SetExitKey(KEY_NULL);
 SetMousePosition(GetScreenWidth()/2, GetScreenHeight()/2);
Texture2D aTexture = LoadTexture("Assets/enemy/blueSlime.png");
  /* theEnemyManager.spawnSlimeEnemy(Vector2{100,100}, "blueSlime.png", xmlFile.getCollisionTileIDs());
  theEnemyManager.spawnSlimeEnemy(Vector2{200,100}, "blueSlime.png", xmlFile.getCollisionTileIDs());
  theEnemyManager.spawnShootingEnemy(Vector2{300,300}, "fireMan.png", xmlFile.getCollisionTileIDs());
   theEnemyManager.smartPtrEnemies[0]->thePlayer = &nPlayer;
    theEnemyManager.smartPtrEnemies[1]->thePlayer = &nPlayer;
    theEnemyManager.smartPtrEnemies[2]->thePlayer = &nPlayer;
    */
   spawnNSlimeEnemies(2, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer);
  nPlayer.destRecPos = chooseValidPos(xmlFile.getCollisionTileIDs(), true); 
  // spawnNShootingEnemies(1, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer);

// Main game loop
    while (!WindowShouldClose() && shouldClose != 1)    // Detect window close button or ESC key
    {
      

        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        DisableCursor();
        // Update
        gameRenderer.update();
        gameRenderer.skillUpdate(nPlayer.skillManagerObject.skillSlotsObject.currentSkills, &nPlayer.skillManagerObject.skillSlotsObject.equippedSkills);
        bool isPaused;
        isPaused =  gameRenderer.getGameIsPaused();
        if(isPaused == false){
         nPlayer.update(xmlFile.getCollisionTileIDs());
      //   theEnemyManager.update();
       theEnemyManager.sUpdate();
         camera.update();
        }
        else{
          EnableCursor();
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
         if(aCurrentMap == water_map){
         ClearBackground(BLUE);
         }
         else{
           ClearBackground(WHITE);
         }
           
            
            DrawFPS(10, 10);  // Draw current FPS
            
            if(isPaused == false){
             
              BeginMode2D(camera.cam);
                xmlFile.new_draw_tilemap();
               // default_map.draw();
                nPlayer.camera1 = camera.cam;
                nPlayer.draw();
                theEnemyManager.sDraw();
           // DrawTextureRec(aTexture, {0,0,144,144}, {100,100}, WHITE);

                

            EndMode2D();
            nPlayer.drawOffCamera();
            mouseHandlerObject.draw();
            
            }
            else{
              if(gameRenderer.whichPause == 4){
                BeginMode2D(camera.cam);
                xmlFile.new_draw_tilemap();
                nPlayer.draw();

                EndMode2D();
              }
              gameRenderer.drawPauseMenu();
              nPlayer.drawOffCamera();
              
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
    for(int c = 0; c < nPlayer.fxPlayerObject.textures.size(); c++){
      UnloadTexture(nPlayer.fxPlayerObject.textures[c]);
    }
    theEnemyManager.deLoadTextures();
    for(int d = 0; d < theEnemyManager.enemies.size(); d++){
    UnloadTexture(theEnemyManager.enemies[d].enemyFrameUtility.texture);  
    }
    theEnemyManager.deLoadProjectiles();
    for(int i = 0; i < theEnemyManager.smartPtrEnemies.size(); i++){
      theEnemyManager.smartPtrEnemies[i]->unloadTexture();
      for(int j = 0; j < theEnemyManager.smartPtrEnemies.size(); j++){ // 0 clue why there is two loops
        UnloadTexture(theEnemyManager.smartPtrEnemies[i]->enemyFrameUtility.texture);
      }
    }
    nPlayer.deload();
    manager.unloadAll();
    UnloadTexture(mouseHandlerObject.mouseTexture);
    UnloadTexture(aTexture);
    CloseAudioDevice(); // Close sound device
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}
#endif