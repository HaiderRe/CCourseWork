#ifndef game_renderer_h
#define game_renderer_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "tile_map.hpp"
#include "mouseHandler.hpp"
namespace enemy_objects_h_1 {
    class projectile;
};
namespace game_renderer_h_1{ //One of the functions of this namespace is to be global 
// Game_renderer might not be the best name 
    struct textureWrapper{ //Needed as we will be Dynamically DeAlloc textures using different methods 
    Texture2D texture;
    bool isLoaded = true;  // This is what we need to track whether a texture is loaded or not, this prevents unloading an already loaded texture.
    };
    class game_renderer{
    public:
    bool gameIsPaused = false;
    std::vector<Texture2D> texturesToBeDeAllocated;
    mouseHandlerClass mouseHandlerObject;
    int whichPause = -1;  //0 = pause menu, 1 = inventory, 2 = map
    game_renderer(){
        gameIsPaused = false; // Variable to hold whether the game is paused or not
        texturesToBeDeAllocated.push_back(LoadTexture("Assets/UI/GUI.png"));
    }                              
    std::vector<textureWrapper> textureDeAlloc;
    std::vector<Texture2D> getTexturesToBeDeAllocated(){
        return texturesToBeDeAllocated;
    }
    bool DeAlloc();
    void pauseMenu(){ //Needs to have buttons to go to options and quit and resume
        Rectangle sourceRect = {10,192,44,64};
        Rectangle destRect = {GetScreenWidth()/2, GetScreenHeight()/2, 264, 384};
        DrawTexturePro(texturesToBeDeAllocated[0], sourceRect, destRect, {132,192}, 0.00f, WHITE);

    }
    void optionLogic(){
        std::string inventoryText = "Options"; 
        DrawText(inventoryText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
    }
    void inventoryMenu(){ //Needs to Have buttons and logic including what invetory items are in the inventory
        std::string inventoryText = "Inventory"; 
        DrawText(inventoryText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
    }
    void mapMenu(){ //Needs to have logic to draw the map
        std::string mapText = "Map";
        DrawText(mapText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
    }
    int menuLogic(){
        mouseHandlerObject.update();
        if(whichPause ==0){
            std::vector<Rectangle> buttons;
            Rectangle resumeButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2 - 128, 264, 64};
            Rectangle optionsButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2  - 32, 264, 64};
            Rectangle exitButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2 + 64, 264, 64};
            buttons.push_back(resumeButton);
            buttons.push_back(optionsButton);
            buttons.push_back(exitButton);
            int buttonClicked = mouseHandlerObject.isClicked(buttons);
            if(buttonClicked == 0){
                gameIsPaused = false;
                whichPause = -1;
            }
            else if(buttonClicked == 1){
                whichPause = 3;
            }
            else if(buttonClicked == 2){
                return 1;
            }
        }
        return 0;
    }
    void drawPauseMenu(){
        ClearBackground(BLACK);
        if(whichPause == 0){  //0 = pause menu, 1 = inventory, 2 = map, 3 = options
            pauseMenu();
           /* Rectangle resumeButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2 - 128, 264, 64};
            Rectangle optionsButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2  - 32, 264, 64};
            Rectangle exitButton = {GetScreenWidth()/2 - 132, GetScreenHeight()/2 + 64, 264, 64};
            DrawRectangle(resumeButton.x, resumeButton.y, resumeButton.width, resumeButton.height, RED);
            DrawRectangle(optionsButton.x, optionsButton.y, optionsButton.width, optionsButton.height, RED);
            DrawRectangle(exitButton.x, exitButton.y, exitButton.width, exitButton.height, RED);
            */
        }
        else if(whichPause == 1){
            inventoryMenu();
        }
        else if(whichPause == 2){
            mapMenu();
        }
        else if(whichPause == 3){
            optionLogic();
        }
    }
    
    void update(){
        if(IsKeyPressed(KEY_ESCAPE)){
            gameIsPaused = !gameIsPaused;
            if(gameIsPaused == true){
                whichPause = 0;
            }
            else{
                whichPause = -1;
            }
        }
        if(IsKeyPressed(KEY_I)){
            gameIsPaused = !gameIsPaused;
            if(gameIsPaused == true){
                whichPause = 1;
            }
            else{
                whichPause = -1;
            }
        }
        if(IsKeyPressed(KEY_M)){
            gameIsPaused = !gameIsPaused;
            if(gameIsPaused == true){
                whichPause = 2;
            }
            else{
                whichPause = -1;
            }
        }
    }
    bool getGameIsPaused(){
        return gameIsPaused; //Returns whether the game is paused or not
    }
    bool getWhichPause(){
        return whichPause; //Returns which pause menu is open
    }
}; 

bool game_renderer::DeAlloc(){
    for(textureWrapper &textureToBe : textureDeAlloc ){ //DeAlloc textures that are loaded, uses the textureWrapper struct
        if(textureToBe.isLoaded == true){
            UnloadTexture(textureToBe.texture);
        }
    }
    return true;
}
class state_manager{
    public:
    tilemap_ns::tilemap currentTilemap;
 };
}
#endif