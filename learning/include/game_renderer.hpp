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
#include "skillDec.hpp"
using namespace skills_NS;
namespace enemy_objects_h_1 {
    class projectile;
};
namespace game_renderer_h_1{ //One of the functions of this namespace is to be global 
// Game_renderer might not be the best name 
    struct textureWrapper{ //Needed as we will be Dynamically DeAlloc textures using different methods 
    Texture2D texture;
    bool isLoaded = true;  // This is what we need to track whether a texture is loaded or not, this prevents unloading an already loaded texture.
    };
    struct specialInvetory{
        Texture2D texture;
        std::string name; 
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
    std::vector<inventoryItem> allInventoryItems; //Holds all the inventory items in the game, and their amount that the player has 
    std::vector<inventoryItem> inventoryItems; //Holds the inventory items that the player has, and their amount
    std::vector<specialInvetory> inventoryTextures; //Holds the textures of the inventory items 
    std::vector<skill> currentlyOwnedSkills;  // Holds the skills that the player has
    std::vector<skill>* equippedSkills; // Holds the skills that the player has equipped
    int skillMenuIndex = 0;
    int whichPause = -1;  //0 = pause menu, 1 = inventory, 2 = map
    void adminGiveAll(){
        std::clog << "Giving all items" << std::endl;
        for(int i = 0; i < allInventoryItems.size(); i++){
            allInventoryItems[i].amount = 1;
        }
    }
    void giveItem(std::string name, int amount){
        for(int i = 0; i < allInventoryItems.size(); i++){
            if(allInventoryItems[i].name == name){
                allInventoryItems[i].amount += amount;
            }
        }
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
        texturesToBeDeAllocated.push_back(LoadTexture("Assets/UI/GUI.png")); // Index is 0
        texturesToBeDeAllocated.push_back(LoadTexture("Assets/UI/Orange_Button_Icons.png")); // Index is 1
         addAllInventoryItem();
         loadInventoryTextures();
         adminGiveAll(); // Stop Calling This after testing
    }                              
    std::vector<textureWrapper> textureDeAlloc;
    std::vector<Texture2D> getTexturesToBeDeAllocated(){
        return texturesToBeDeAllocated;
    }
   void loadInventoryTextures(){ //Loads the textures of the inventory items
    for(int i = 0; i < allInventoryItems.size(); i++){
        specialInvetory item; 
        item.name = allInventoryItems[i].name;
        std::string filePath = "Assets/Items/" + allInventoryItems[i].name;
        item.texture = LoadTexture(filePath.c_str());
        if (item.texture.id <= 0) {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            continue;
        }
        inventoryTextures.push_back(item); // Load the texture of the item        
        texturesToBeDeAllocated.push_back(item.texture); // Add the texture to the textures to be DeAllocated vector
    }
}
 

    bool DeAlloc(); //DeAllocates all the textures that are loaded
    void pauseMenu(){ //Needs to have buttons to go to options and quit and resume
        Rectangle sourceRect = {10,192,44,64};
        Rectangle destRect = {GetScreenWidth()/2, GetScreenHeight()/2, 264, 384};
        DrawTexturePro(texturesToBeDeAllocated[0], sourceRect, destRect, {132,192}, 0.00f, WHITE);

    }
    void optionLogic(){
        std::string inventoryText = "Options"; 
        DrawText(inventoryText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
    }
    int amountOfInventoryItems(){ // Returns the amount of inventory items that are in the inventory, by checking the amount of each item
    if(true){ // False as we dont have any textures yet
        inventoryItems.clear(); // Clear the vector so that it can be repopulated as otherwise it will just keep adding to the vector 
    } 
        int total = 0;
        for(int i = 0; i < allInventoryItems.size(); i++){
            if(allInventoryItems[i].amount > 0){
                total++;
                if(true){ // False as we dont have any textures yet
                inventoryItems.push_back(allInventoryItems[i]); // Add the item to the inventoryItems vector
                }
                
            }
        }
        return total;
    }
    int getIndexOfinventoryTextures(std::string name){
        for(int i = 0; i < inventoryTextures.size(); i++){
            if(inventoryTextures[i].name == name){ // fix later
                return i;
            }
        }
        return -1;
    }

    
    void inventoryMenu(){ //Needs to Have buttons and logic including what invetory items are in the inventory
      //  std::string inventoryText = "Inventory"; 
        //DrawText(inventoryText.c_str(), GetScreenWidth()/2, GetScreenHeight()/2, 20, WHITE);
        int xOffset = GetScreenWidth()/16;
        int yOffset = GetScreenHeight()/16;
        int borderThickness = 12;
        int buttonRight= 192;
        int buttonRightOffX = 64;
        int buttonLeft = 224;
        int buttonLeftOffX = 64; 
        int amountOfItems = amountOfInventoryItems(); 
        int pages = amountOfItems / 144; // Items 0 - 143 are first on page 0 if the player has all items, meaning that items in the inventory are sorted by id 
        bool buttonLeftActive = false;
        bool buttonRightActive = false;
        int currentPage = 0;
        if(pages > 0){
            buttonRightActive = true;
        }
        // For next time, sort out displaying items based on pages, and then add the ability to scroll through pages using the buttons
        Rectangle Border = {4.8  * xOffset - borderThickness/2 , 2 * yOffset - borderThickness/2, 12 * yOffset + borderThickness, 12 * yOffset + borderThickness};
        DrawRectangle(Border.x, Border.y, Border.width, Border.height, BLACK);
        Color grey = {31, 36, 40, 255};
        std::cout << "inventoryItems size: " << inventoryItems.size() << std::endl;
       for(int i = 0; i <  12; i++){
        for(int j = 0; j < 12; j++){
                // In each rectangle have a smaller rectangle that is a square that fits in the rectangle
                Rectangle destRect2 = {4.8 * xOffset + (i * yOffset) + 2, 2 * yOffset + (j * yOffset) + 2, yOffset - 4,  yOffset - 4};
               // DrawRectangleLines(destRect.x, destRect.y, destRect.width, destRect.height, RED);
                DrawRectangle(destRect2.x, destRect2.y, destRect2.width, destRect2.height, grey);
                if(inventoryItems.size() > (i + (j * 12) )){ 
                Rectangle destRect = {4.8 * xOffset + (i * yOffset) + 16, 2 * yOffset + (j * yOffset) + 16 , yOffset + 4,  yOffset + 4};
                int indexOf = getIndexOfinventoryTextures(inventoryItems[i + (j * 12) + (currentPage * 144)].name);
                if (indexOf < 0) {
                    std::cerr << "Invalid index for inventoryTextures: " << indexOf << std::endl;
                    continue;
                }
                   DrawTexturePro(inventoryTextures[indexOf].texture, {0,0,32,32}, destRect, {16,16}, 0.00f, WHITE);
                   // DrawTexturePro(inventoryItems[], {0,0,32,32}, destRect, {16,16}, 0.00f, WHITE);
                    DrawText(std::to_string(inventoryItems[i + (j * 12) + (currentPage * 144)].amount).c_str(), destRect.x + 4, destRect.y + 4, 20, WHITE);
                }
            }
        }
        //Draw right arrow
        int cButtonRightX = 0;
        if(buttonRightActive != true){
            cButtonRightX = buttonRightOffX;
        }
            Rectangle sourceRect = {cButtonRightX, buttonRight, 32, 32};
            Rectangle destRect = {GetScreenWidth()/2 + 4 * xOffset - 32, GetScreenHeight()/2, 128, 128};
            DrawTexturePro(texturesToBeDeAllocated[1], sourceRect, destRect, {16,16}, 0.00f, WHITE);
        //Draw left arrow 
        int cButtonLeftX = 0;
        if(buttonLeftActive != true){
            cButtonLeftX = buttonLeftOffX;
        }
            Rectangle sourceRect2 = {cButtonLeftX, buttonLeft, 32, 32}; 
            Rectangle destRect2 = {GetScreenWidth()/2 - (4 * xOffset + 8), GetScreenHeight()/2, 128, 128};
            DrawTexturePro(texturesToBeDeAllocated[1], sourceRect2, destRect2, {16,16}, 0.00f, WHITE);
        
        
        
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
    void skillUpdate(std::vector<skill> skills1, std::vector<skill>* skills2){
        currentlyOwnedSkills = skills1;
        equippedSkills = skills2;
    }

    
    void skillMenu(){
        Color grey = {128,128,128, 255};
        Color highlightColor = {0, 123, 255, 100};
        Vector2 mousePos = GetMousePosition();
        for(int i = 0; i < currentlyOwnedSkills.size(); i++){
            // Draw the backround Rectangle for colour
            DrawRectangle((GetScreenWidth()/2 + (i * 64) - 32)- (currentlyOwnedSkills.size() * 32), GetScreenHeight()/2 - 32, 64, 64,grey);
            // Draw the skill icon
            DrawTexturePro(currentlyOwnedSkills[i].skillIcon, {0,0,32,32}, {float(GetScreenWidth()/2 + (i * 64) - (currentlyOwnedSkills.size() * 32)), float(GetScreenHeight()/2), 64, 64}, {32,32}, 0.00f, WHITE);
             // Draw Outlines
            DrawRectangleLines(float(GetScreenWidth()/2 + (i * 64) - 32) - (currentlyOwnedSkills.size() * 32), float(GetScreenHeight()/2 - 32), 64, 64, BLACK);
            // Draw Text for Number on the bottom right of skill 
            DrawText(std::to_string(i + 1).c_str(), float(GetScreenWidth()/2 + (i * 64) - 32) - (currentlyOwnedSkills.size() * 32) + 48, float(GetScreenHeight()/2 - 32) + 48, 20, WHITE);
            //Draw text where the skill slots 
            if(i < 4){
            DrawText(std::to_string(i + 1).c_str(), float(GetScreenWidth()/2 - 128) + (i * 64) , float(GetScreenHeight() - 64), 20, WHITE);
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, {float(GetScreenWidth()/2 + (i * 64) - 32) - (currentlyOwnedSkills.size() * 32), float(GetScreenHeight()/2 - 32), 64, 64})){
                std::cout << "size of equippedSkills is " << equippedSkills->size() << std::endl;
                if(equippedSkills->size() > 3){
                    equippedSkills->erase(equippedSkills->begin() + skillMenuIndex); // removes first element of the vector
                    equippedSkills->insert(equippedSkills->begin() + skillMenuIndex,currentlyOwnedSkills[i]); // inserts the skill into the vector
                    skillMenuIndex++; // increments the skillMenuIndex
                    if(skillMenuIndex > 3){
                        skillMenuIndex = 0;
                    }
                }
                else{
                    equippedSkills->push_back(currentlyOwnedSkills[i]);
                }
                
            }
        }
        if(equippedSkills->size() > 3){ //adds highlight to the currently selected skill
        Rectangle destRec = { 0, 0, 64, 64};
        destRec.x = (GetScreenWidth()/2 - 128) + (skillMenuIndex * 64);
        destRec.y = GetScreenHeight() - 64;
        DrawRectangle(destRec.x, destRec.y, destRec.width, destRec.height, highlightColor); 
        }
        
       
    }
    void drawPauseMenu(){
        if(whichPause == -1){
            return;
        }
        if(whichPause != 4){
          ClearBackground(BLACK);
        }
        
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
        else if(whichPause == 4){
            skillMenu();
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
        if(IsKeyPressed(KEY_L)){
            gameIsPaused = !gameIsPaused;
            if(gameIsPaused == true){
                whichPause = 4;
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