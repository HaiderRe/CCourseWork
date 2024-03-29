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
#include <unordered_map> 
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
#include "include/level.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
using namespace tilemap_ns;
/*enum currentMap {
    water_map,
    default_map,
    test_map
};
*/

void drawMainMenuText(Font aCustomFont){
  Vector2 textPosition = {(float) GetScreenWidth() / 2 - GetScreenWidth() / 8, 200};
   int outlineThickness = 3;
        for (int x = -outlineThickness; x <= outlineThickness; x++){
            for (int y = -outlineThickness; y <= outlineThickness; y++){
                DrawTextEx(aCustomFont, "Legend of Rehawi", Vector2{textPosition.x + x, textPosition.y + y}, 80, 1, BLACK);
            }
        }
        DrawTextEx(aCustomFont, "Legend of Rehawi", textPosition, 80, 1, ORANGE);
}
std::vector<Rectangle> stringToSourceRectV(std::string text) {
    std::vector<Rectangle> sourceRects;
    std::string charset = "0123456789AaaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"; 
    std::unordered_map<char, int> charToIndex;
    for (int i = 0; i < charset.size(); ++i) {
        if (charToIndex.find(charset[i]) == charToIndex.end()) { 
            charToIndex[charset[i]] = i;
        }
    }
    int width = 32; 
    int height = 32;
    int charsPerRow = 18; 
    for (char c : text) {
        auto it = charToIndex.find(c);
        if (it != charToIndex.end()) {
            int index = it->second;
            int x = (index % charsPerRow) * width;
            int y = (index / charsPerRow) * height;           
            Rectangle rect = { (float)x, (float)y, (float)width, (float)height};
            sourceRects.push_back(rect);
        }
    }
    return sourceRects;
}
void drawLevelText(std::string aText){
  std::vector<Rectangle> sourceRects = stringToSourceRectV(aText);
}
std::string enumToString(currentMap map) {
    switch (map) {
        case water_map:
            return "water_tilemap.xml";
        case default_map:
            return "testing_functionalilty_of_parser.xml";
        case test_map:
            return "testing_functionalilty_of_parser.xml";
        case town_map:
            return "town.xml";
        case grass_map:
            return "new_map.xml";
        default:
            return "Unknown";
    }
}
Vector2 chooseValidPosPlayer(std::vector<std::vector<int>> collisionTileIDs, bool ignoreFirstRow){
  Vector2 validPos = {0.00f, 0.00f};
  validPos.x = 32 * 16;
  validPos.y = 32 * 16;
  return validPos;
}
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
Vector2 chooseValidPosRandom(std::vector<std::vector<int>> collisionTileIDs, Rectangle enemyRect, bool isSlime, currentMap aCurrentMap1){
  Vector2 validPos = {0.00f, 0.00f};
  SetRandomSeed(GetTime());
  Vector2 center = {0.00f, 0.00f};
  Vector2 widthHeight = {0.00f, 0.00f};
  int randXMax = 63;
  int randYMax = 63;
  int randXMin = 0;
  int randYMin = 0;
  if(enumToString(aCurrentMap1) == "water_tilemap.xml"){
    randYMax = 54;
    randYMin = 26;
    randXMin = 10;
    randXMax = 53;
  }
  else if(enumToString(aCurrentMap1) == "town.xml"){
    randYMax = 41;
    randYMin = 20;
  }
  else{
    randYMax = 63;
    randYMin = 0;
  }
  if(isSlime){
    center = {enemyRect.x, enemyRect.y};
    widthHeight = {0.00f, 0.00f};
  }
  else{
    center = {enemyRect.x + enemyRect.width/2, enemyRect.y + enemyRect.height/2};
    widthHeight = {enemyRect.width, enemyRect.height};
  }
  int amountOfIter = 0;
  while(true){
    int randX = GetRandomValue(0, 63);
    int randY = GetRandomValue(0, 63);
    Vector2 randPos = {randX * 16, randY * 16};
    randPos.x = randPos.x + widthHeight.x/2;
    randPos.y = randPos.y + widthHeight.y/2;
    randX = randPos.x / 16;
    randY = randPos.y / 16;
    if(randX >= 0 && randX < collisionTileIDs.size() && randY >= 0 && randY < collisionTileIDs[0].size()){
    if(collisionTileIDs[randX][randY] == 0 && randY > randYMin && randY < randYMax){
      validPos.x = randX * 16;
      validPos.y = randY * 16;
      return validPos;
    }
    }
    amountOfIter = amountOfIter + 1;
    if(amountOfIter > 1000000){ // Just in case it gets stuck in a loop
      return chooseValidPos(collisionTileIDs);
    }
  }
    
  
  std::clog << "no valid pos found" << std::endl;
  return validPos;
}
void spawnNShootingEnemies(int amouunt, enemyObjects_NS::enemyManager& theEnemyManager, std::vector<std::vector<int>> collisionTileIDs, player_objects::player& nPlayer, currentMap aCurrentMap){
  for(int i = 0; i < amouunt; i++){
    theEnemyManager.spawnShootingEnemy(chooseValidPosRandom(collisionTileIDs, Rectangle{0.00f, 0.00f, 64, 64}, false, aCurrentMap), "fireMan.png", collisionTileIDs);
   // theEnemyManager.smartPtrEnemies[i]->thePlayer = &nPlayer;
    theEnemyManager.smartPtrEnemies.back()->thePlayer = &nPlayer;
  }
}
void spawnNSlimeEnemies(int amount, enemyObjects_NS::enemyManager& theEnemyManager, std::vector<std::vector<int>> collisionTileIDs, player_objects::player& nPlayer, currentMap aCurrentMap){
  for(int i = 0; i < amount; i++){
    theEnemyManager.spawnSlimeEnemy(chooseValidPosRandom(collisionTileIDs, Rectangle{0.00f, 0.00f, 0.00f, 0.00f}, true, aCurrentMap), "blueSlime.png", collisionTileIDs);
  ///  theEnemyManager.smartPtrEnemies[i]->thePlayer = &nPlayer;
     theEnemyManager.smartPtrEnemies.back()->thePlayer = &nPlayer;

  }
}
bool drawMainMenu(Texture2D aBigMenuTexture, Texture2D aLogo) {
    Vector2 mousePos = GetMousePosition();
    mousePos.x = mousePos.x + 28;
    mousePos.y = mousePos.y + 28; // Offset the mouse position

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Rectangle destRec = {(float)(screenWidth / 2 - (screenWidth / 24)),(float)(screenHeight / 2 - screenHeight / 8 - screenHeight / 24 + screenHeight / 8), (float)(screenWidth / 12),  (float)(screenHeight / 12)};
    Rectangle destRec1 = destRec;
    destRec1.width = GetScreenWidth();
    destRec1.height = GetScreenHeight();
    destRec1.x = 0;
    destRec1.y = 0;
   // DrawTexturePro(aLogo, {0,0, (float)aLogo.width, (float)aLogo.height}, destRec1, {0,0}, 0.0f, WHITE);
    DrawTexturePro(aBigMenuTexture, {0, 0, (float)aBigMenuTexture.width, (float)aBigMenuTexture.height}, destRec, {0, 0}, 0.0f, WHITE);
    
    
    
    const char* text = "Play";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 40, 1);
    DrawText(text, destRec.x + (destRec.width - textSize.x) / 2, destRec.y + (destRec.height - textSize.y) / 2, 40, Color{232, 222, 149,255});
    bool buttonClicked = false;
    if (CheckCollisionPointRec(mousePos, destRec)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            buttonClicked = true;
        }
    }
    return buttonClicked;
}

 void DrawParallaxBackground(Texture2D bg, Vector2* bgPos, float speed){
 Rectangle windowRect = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
Vector2 origin = {0, 0};
float windowWidth = (float)GetScreenWidth();
float windowHeight = (float)GetScreenHeight();
bgPos->x -= speed;
if(bgPos->x <= -windowWidth){
bgPos->x += windowWidth;
}
   Rectangle sourceRect = {0, 0, bg.width, bg.height};
   DrawTexturePro(bg, sourceRect, Rectangle{bgPos->x, 0, windowWidth, windowHeight}, origin, 0.0, WHITE);
   DrawTexturePro(bg, sourceRect, Rectangle{bgPos->x + windowWidth, 0, windowWidth, windowHeight}, origin, 0.0, WHITE);
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
    int levelWait = 0;
    int maxLevelwait = 600;
    levelManager aLevelManager;
    SoundManager& manager = SoundManager::getInstance();
    game_renderer_h_1::game_renderer gameRenderer;
    player_objects::player nPlayer;
    camera_h::camera_class camera(nPlayer);
    mouseHandler::mouseHandlerClass mouseHandlerObject;
    upgrade aUpgrade;
    int shouldClose = 0;
    bool mainMenuDone = false;
    Texture2D mainMenuButtonBig = LoadTexture("Assets/UI/mainMenu/active6.png");
    Texture2D logo = LoadTexture("Assets/UI/mainMenu/legendOfRehawi.png");
    
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
 // my_xml_parser::file_to_read xmlFile("include/water_tilemap.xml"); // Water_map
 my_xml_parser::file_to_read xmlFile("include/new_map.xml");
 currentMap aCurrentMap = grass_map;
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
  // spawnNSlimeEnemies(2, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer);
  nPlayer.destRecPos = chooseValidPosPlayer(xmlFile.getCollisionTileIDs(), true); 
  //spawnNShootingEnemies(1, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer);
nPlayer.skillManagerObject.skillSlotsObject.currentSkills.push_back(nPlayer.skillManagerObject.skillSlotsObject.skills[6]);
Texture2D bg1 = LoadTexture("Assets/UI/mainMenu/8.png");
Texture2D bg2 = LoadTexture("Assets/UI/mainMenu/7.png");
Texture2D bg3 = LoadTexture("Assets/UI/mainMenu/6.png");
Texture2D bg4 = LoadTexture("Assets/UI/mainMenu/5.png");
Texture2D bg5 = LoadTexture("Assets/UI/mainMenu/4.png");
Texture2D bg6 = LoadTexture("Assets/UI/mainMenu/3.png");
Texture2D bg7 = LoadTexture("Assets/UI/mainMenu/2.png");
Texture2D bg8 = LoadTexture("Assets/UI/mainMenu/1.png");
    Vector2 bg1Pos = {0, 0};
    Vector2 bg2Pos = {0, 0};
    Vector2 bg3Pos = {0, 0};
    Vector2 bg4Pos = {0, 0};
    Vector2 bg5Pos = {0, 0};
    Vector2 bg6Pos = {0, 0};
    Vector2 bg7Pos = {0, 0};
    Vector2 bg8Pos = {0, 0};
    Rectangle windowRect = {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()};
    Vector2 origin = {0, 0};
  Font customFont = LoadFont("Assets/font/ThaleahFat.ttf");  
// Main game loop
    while (!WindowShouldClose() && shouldClose != 1 )    // Detect window close button or ESC key
    {
      if(mainMenuDone == false){
        BeginDrawing();
        ClearBackground(WHITE);
    
        DrawParallaxBackground(bg1, &bg1Pos, 0.5);
        DrawParallaxBackground(bg2, &bg2Pos, 1.0);
        DrawParallaxBackground(bg3, &bg3Pos, 1.5);
        DrawParallaxBackground(bg4, &bg4Pos, 2.0);
        DrawParallaxBackground(bg5, &bg5Pos, 2.5);
        DrawParallaxBackground(bg6, &bg6Pos, 3.0);
        DrawParallaxBackground(bg7, &bg7Pos, 3.5);
        DrawParallaxBackground(bg8, &bg8Pos, 4.0);
        drawMainMenuText(customFont);

      mainMenuDone = drawMainMenu(mainMenuButtonBig,logo);
      EndDrawing();
      if(mainMenuDone == true){
        UnloadTexture(mainMenuButtonBig);
        UnloadTexture(logo);
        UnloadTexture(bg1);
        UnloadTexture(bg2);
        UnloadTexture(bg3);
        UnloadTexture(bg4);
        UnloadTexture(bg5);
        UnloadTexture(bg6);
        UnloadTexture(bg7);
        UnloadTexture(bg8);
        UnloadFont(customFont);
      }
      }
      else{
      //if(nPlayer.health <= 0.00f){
     //   break;
     // }
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
        aLevelManager.update(theEnemyManager.howManyEnemies());
       // std::clog << "enemies left: " << theEnemyManager.howManyEnemies() << std::endl;
        if(aLevelManager.getCurrentMap() != aCurrentMap){
          std::string map = enumToString(aLevelManager.getCurrentMap());
          std::string path = "include/" + map;
         // UnloadTexture(xmlFile.mapTexture.texture); 
          UnloadTexture(xmlFile.get_map_texture().texture);
          xmlFile = my_xml_parser::file_to_read(path);
           xmlFile.set_map_texture();
            xmlFile.set_column();
            aCurrentMap = aLevelManager.getCurrentMap();
            nPlayer.destRecPos = chooseValidPosPlayer(xmlFile.getCollisionTileIDs(), true); 
        }
        if(aLevelManager.isLevelComplete() == true){
          if(levelWait > 0){
            levelWait--;
            if(IsKeyPressed(KEY_F)){
                levelWait = -1;
              }
            if(levelWait == 0){
              levelWait = -1;
              
            }
          }
          else if (levelWait == 0){
            aUpgrade.getUpgrade();
            aUpgrade.getUpgrade();
            aUpgrade.getUpgrade();
            levelWait = maxLevelwait;
          }
          else{
          aLevelManager.newLevelSetup();
          theEnemyManager.reset();
          int amount = aLevelManager.enemiesToSpawn;
          int amountOfSlime = amount / 2 ;
          int amountOfShooting = amount - amountOfSlime;
          spawnNSlimeEnemies(amountOfSlime, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer, aCurrentMap);
          spawnNShootingEnemies(amountOfShooting, theEnemyManager, xmlFile.getCollisionTileIDs(), nPlayer, aCurrentMap);
          levelWait = 0;

          }
        }
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        std::vector<std::vector<int>> xmlTileIDs = xmlFile.get_tileIDs();
         if(nPlayer.health <= 0){
          break;
         }
         BeginDrawing();
         if(aCurrentMap == water_map){
         ClearBackground(BLUE);
         }
         else if(aCurrentMap == town_map){
          ClearBackground(GRAY);
         }
         else if(aCurrentMap == grass_map){
            ClearBackground(Color{114, 117, 27,255});
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
            if(levelWait > 0){
              DrawText("Level Complete", GetScreenWidth() / 2 - 10, 100, 20, BLACK);
              DrawText(std::to_string(levelWait).c_str(), GetScreenWidth()/2 - 10, 120, 20, BLACK);
              DrawText("Press F to continue", GetScreenWidth()/2 - 10, 140, 20, BLACK);
              std::string stringUpgrade = aUpgrade.draw(); 
              if(stringUpgrade != "null"){
                std::clog << "upgrade = " << stringUpgrade << std::endl;
                nPlayer.chooseUpgrade(stringUpgrade);
              }
            }
            
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
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
      std::vector<Texture2D> gameOver; 
      for(int i = 1; i < 29; i++){
        gameOver.push_back(LoadTexture(("Assets/UI/gameOver/" + std::to_string(i) + ".png").c_str()));
      }
      int frameWidth  = 1542;
      int frameHeight = 1201;
      int frameSpeed = 4;
      int currentFrame  = 0; 
      int framesCounter = 0;
      int maxFrames = 28;
      bool isDone = false;
      int frame = 0;
      Rectangle frameRec = {0, 0, frameWidth, frameHeight};
      Rectangle frameRec1= {0, 0, frameWidth, frameHeight};

      while(isDone == false){
      framesCounter++;
              frameRec.y = frameHeight;
              if (framesCounter >= (60/frameSpeed))
              {
                  framesCounter = 0;
                  currentFrame++;
                  if (currentFrame > maxFrames) {
                      currentFrame = 0;
                      isDone = true;
                  }
                  frameRec.x = frameWidth * currentFrame;
                  frame = currentFrame;
              }
              BeginDrawing();
              ClearBackground(BLACK);
           //   DrawTextureRec(gameOver[frame], frameRec1, {0,0}, WHITE);
              DrawTexturePro(gameOver[frame], frameRec, {0,0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0,0}, 0.00f, WHITE);
              EndDrawing();
      }
    
     for (int i = 0; i < gameOver.size(); i++){
      UnloadTexture(gameOver[i]);
    }
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
    aUpgrade.deload();
    UnloadTexture(mouseHandlerObject.mouseTexture);
    UnloadTexture(aTexture);
    CloseAudioDevice(); // Close sound device
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}
#endif