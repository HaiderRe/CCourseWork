
#ifndef level_h
#define level_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "skillDec.hpp"
   enum currentMap {
    water_map,
    default_map,
    test_map,
    town_map,
    grass_map
};
class levelManager{
      public: 
      currentMap aCurrentMap = grass_map;
      int currentLevel = 0; 
      int enemiesLeft = 0;
      int enemiesKilled = 0;
      int enemiesSpawned = 0;
      int enemiesToSpawn = 0;
      bool levelComplete = false;
      bool intialLevelCompelete = false;
      
      void update(int AEnemiesLeft){
        if(intialLevelCompelete == true){
            return;
        }
        enemiesKilled += (enemiesSpawned - AEnemiesLeft);
        if(AEnemiesLeft == 0 ){
          levelComplete = true;
          intialLevelCompelete = true;
          currentLevel += 1;
        }
        
      }
      int newLevelSetup(){
        enemiesKilled = 0;
        enemiesSpawned = 0;
        enemiesToSpawn = 0;
        enemiesLeft = 0;
        levelComplete = false;
        intialLevelCompelete = false;
        setEnemiesToSpawn();
        return enemiesToSpawn;
      }
      currentMap getCurrentMap(){
        if(currentLevel == 5){
            aCurrentMap = water_map;
        }
        else if(currentLevel == 10){
          aCurrentMap = town_map;
        }
        return aCurrentMap;
      }
      void setEnemiesToSpawn(){
        enemiesToSpawn = 5 + (currentLevel * 4);
        enemiesLeft = enemiesToSpawn;
      }
      bool isLevelComplete(){
        return levelComplete;
      }
};
class upgrade{
  public: 
   std::vector<std::string> upgradeNames;
   std::string currentUpgrade;
   std::vector<std::string> currentUpgradeChoices;
   std::string chosenUpgrade;
   Texture2D textTexture = LoadTexture("Assets/UI/NS_UI_Gold_Icons_NoOutline.png");
   int textOffset = 30;
   upgrade(){
      upgradeNames.push_back("Health");
      upgradeNames.push_back("Damage");
     // upgradeNames.push_back("Speed");
      upgradeNames.push_back("Health Regen");
      upgradeNames.push_back("Armor");
      upgradeNames.push_back("Skill");
   }
   void drawSkill(Rectangle aDestRec){
    Rectangle sourceRectS = {416, 64,32,32};
    Rectangle sourceRectk = {448,32,32,32};
    Rectangle sourceRecti = {320,32,32,32};
    Rectangle sourceRectl = {512,32,32,32};
    Rectangle destRec = aDestRec;
     DrawTexturePro(textTexture, sourceRectS,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectk,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecti,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectl,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectl,destRec, {0.00f}, {0.00f}, WHITE);
   }
   void drawHealthRegen(Rectangle aDestRec){
    Rectangle sourceRectH = {224,32, 32,32};
    Rectangle sourceRecte = {64,32,32,32};
    Rectangle sourceRecta = {384, 0, 32,32};
    Rectangle sourceRectl = {512,32,32,32};
    Rectangle sourceRectt = {512,64,32,32};
    Rectangle sourceRecth = {256,32,32,32};
     Rectangle sourceRectR = {352, 64, 32, 32};

      Rectangle sourceRectg = {192,32,32,32};

      Rectangle sourceRectn = {64,64,32,32};
      Rectangle destRec = aDestRec;
    DrawTexturePro(textTexture, sourceRectH,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecte,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecta,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectl,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectt,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecth,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + (textOffset * 2);
    DrawTexturePro(textTexture, sourceRectR,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecte,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectg,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecte,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectn,destRec, {0.00f}, {0.00f}, WHITE);
    


   }
   void drawDamage(Rectangle aDestRec){
    Rectangle sourceRectD = {544,0,32,32};
    Rectangle sourceRecta = {384, 0, 32,32};
    Rectangle sourceRectm = {0,64,32,32};

    Rectangle sourceRectg = {192,32,32,32};
    Rectangle sourceRecte = {64,32,32,32};
     Rectangle destRec = aDestRec;
      DrawTexturePro(textTexture, sourceRectD,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecta,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectm,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecta,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectg,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecte,destRec, {0.00f}, {0.00f}, WHITE);

   }
   void drawArmor(Rectangle aDestRec){
    Rectangle sourceRectA = {312, 0, 32, 32};
    Rectangle sourceRectr = {384, 64, 32, 32};
    Rectangle sourceRectm = {0,64,32,32};
    Rectangle sourceRecto = {192,64,32,32};
    Rectangle destRec = aDestRec;
    DrawTexturePro(textTexture, sourceRectA,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset + 8;
    DrawTexturePro(textTexture, sourceRectr,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectm,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecto,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectr,destRec, {0.00f}, {0.00f}, WHITE);
   }
   void drawHealth(Rectangle aDestRec){
    Rectangle sourceRectH = {224,32, 32,32};
    Rectangle sourceRecte = {64,32,32,32};
    Rectangle sourceRecta = {384, 0, 32,32};
    Rectangle sourceRectl = {512,32,32,32};
    Rectangle sourceRectt = {512,64,32,32};
    Rectangle sourceRecth = {256,32,32,32};
    Rectangle destRec = aDestRec;
    DrawTexturePro(textTexture, sourceRectH,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecte,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecta,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectl,destRec, {0.00f}, {0.00f}, WHITE);
     destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRectt,destRec, {0.00f}, {0.00f}, WHITE);
    destRec.x = destRec.x + textOffset;
    DrawTexturePro(textTexture, sourceRecth,destRec, {0.00f}, {0.00f}, WHITE);
   }
   void drawUpgradeTexture(std::string aCurrentUpgradeChoice, Rectangle aDestRec){
    if(aCurrentUpgradeChoice == "Health"){
      drawHealth(aDestRec);
    }
    else if(aCurrentUpgradeChoice == "Damage"){
      drawDamage(aDestRec);
    }
    else if(aCurrentUpgradeChoice == "Health Regen"){
      drawHealthRegen(aDestRec);
    }
    else if(aCurrentUpgradeChoice == "Skill"){
      drawSkill(aDestRec);
    }
    else if(aCurrentUpgradeChoice == "Armor"){
      drawArmor(aDestRec);
    }
   }
  std::string draw() {
    Vector2 mousePos = GetMousePosition();
    mousePos.x = mousePos.x + 28;
    mousePos.y = mousePos.y + 28;
    chosenUpgrade = "null";
    
    for (int i = 0; i < currentUpgradeChoices.size(); i++) {
        int y = 100 + (i * 50);
       // DrawText(currentUpgradeChoices[i].c_str(), 110, y + 10, 20, BLACK);
        Rectangle destRec = {GetScreenWidth()/2 - GetScreenWidth()/12,  GetScreenHeight() / 2 + y  - GetScreenHeight()/3, 60, 60};
        drawUpgradeTexture(currentUpgradeChoices[i], destRec);
        DrawCircle(mousePos.x, mousePos.y, 5, RED);
        int destRecLinesWidth = 200;
        if(currentUpgradeChoices[i] == "Health Regen"){
          destRecLinesWidth = 400;
        }
        Rectangle destRecLines = {GetScreenWidth()/2- GetScreenWidth()/12, GetScreenHeight()/2 + y - GetScreenHeight()/3, destRecLinesWidth, 50};
      //  DrawRectangleLines(100, y, 200, 50, WHITE);
      DrawRectangleLines(destRecLines.x, destRecLines.y, destRecLines.width, destRecLines.height, WHITE);
       // Rectangle rec = {100.0f, (float)y, 200.0f, 50.0f};
        if (CheckCollisionPointRec(mousePos, destRecLines)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                chosenUpgrade = currentUpgradeChoices[i];
                currentUpgradeChoices.clear();
                return chosenUpgrade;
            }
        }
    }
    return chosenUpgrade;
}

   std::string getUpgrade(){
    if(currentUpgradeChoices.size() > 3){
      std::vector<std::string> emptyChoice;
      emptyChoice = currentUpgradeChoices;
    }
    int index = GetRandomValue(0, upgradeNames.size() - 1);
    currentUpgradeChoices.push_back(upgradeNames[index]);
    return upgradeNames[index];
   }
   void deload(){
    UnloadTexture(textTexture);
   }
};
#endif