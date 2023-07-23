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
#include <filesystem>
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
    struct inventoryItem{
        std::string name;
        int amount;
        int id;
    };
    class game_renderer{
    public:
    bool gameIsPaused = false;
    std::vector<Texture2D> texturesToBeDeAllocated;
    mouseHandlerClass mouseHandlerObject;
    std::vector<inventoryItem> allInventoryItems;

    int whichPause = -1;  //0 = pause menu, 1 = inventory, 2 = map
    void adminGiveAll(){
        std::clog << "Giving all items" << std::endl;

    }
    void addAllInventoryItem(){
        std::string path = "./Assets/Items"; //Relative path to the items folder

    for (std::filesystem::directory_iterator itr(path); itr != std::filesystem::directory_iterator(); ++itr) {
        if (itr->is_regular_file()) {
            
            inventoryItem item;
            item.name = itr->path().filename().string();
            item.amount = 0;
            item.id = allInventoryItems.size() - 1;
            allInventoryItems.push_back(item);
        }
     }
     std::clog << "size of allInventoryItems is " << allInventoryItems.size() << std::endl;
    }
    game_renderer(){
        gameIsPaused = false; // Variable to hold whether the game is paused or not
        texturesToBeDeAllocated.push_back(LoadTexture("Assets/UI/GUI.png"));
         addAllInventoryItem();
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
      //  std::string inventoryText = "Inventory"; 
        //DrawText(inventoryText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
        int xOffset = GetScreenWidth()/16;
        int yOffset = GetScreenHeight()/16;
        int borderThickness = 12;
        
        Rectangle Border = {4.8  * xOffset - borderThickness/2 , 2 * yOffset - borderThickness/2, 12 * yOffset + borderThickness, 12 * yOffset + borderThickness};
        DrawRectangle(Border.x, Border.y, Border.width, Border.height, BLACK);
        Color grey = {31, 36, 40, 255};
        for(int i = 0; i <  12; i++){
            for(int j = 0; j < 12; j++){
                

                Rectangle destRect = {4.8 * xOffset + (i * yOffset), 2 * yOffset + (j * yOffset) , yOffset + 4,  yOffset + 4};
                // In each rectangle have a smaller rectangle that is a square that fits in the rectangle
                Rectangle destRect2 = {4.8 * xOffset + (i * yOffset) + 2, 2 * yOffset + (j * yOffset) + 2, yOffset - 4,  yOffset - 4};
               // DrawRectangleLines(destRect.x, destRect.y, destRect.width, destRect.height, RED);
                DrawRectangle(destRect2.x, destRect2.y, destRect2.width, destRect2.height, grey);
            }
        }
        //Add a thick border around the inventory
      //  Rectangle destRect = {2.4 * xOffset, yOffset, 6 * yOffset, 6 * yOffset}; DrawRectangleLines(destRect.x, destRect.y, destRect.width, destRect.height, BLACK);
        
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
        Color pBlue = {182, 208, 226,255};
 
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
            ClearBackground(pBlue);
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