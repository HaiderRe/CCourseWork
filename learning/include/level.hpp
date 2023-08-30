
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
#endif