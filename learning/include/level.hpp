
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
    test_map
};
class levelManager{
      public: 
      currentMap aCurrentMap = water_map;
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
            aCurrentMap = default_map;
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
   upgrade(){
      upgradeNames.push_back("Health");
      upgradeNames.push_back("Damage");
     // upgradeNames.push_back("Speed");
      upgradeNames.push_back("Health Regen");
      upgradeNames.push_back("Armor");
      upgradeNames.push_back("Skill");
   }
   std::string draw(){
    Vector2 mousePos = GetMousePosition();
    chosenUpgrade = "null";
     for(int i = 0; i < currentUpgradeChoices.size(); i++){
       DrawText(currentUpgradeChoices[i].c_str(), 100, 100 + (i * 50), 20, BLACK);
       DrawRectangle(100, 100 + (i * 50), 200, 50, WHITE);
       if(CheckCollisionPointRec(mousePos, Rectangle{100, (float)(100 + (i * 50)), 200, 50})){
         if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
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
};
#endif