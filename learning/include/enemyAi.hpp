#ifndef enemyAi_h
#define enemyAi_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <memory> 
#include "frameUtility.hpp"  
#include "pathfinder.hpp"
#include "AStar.hpp"
namespace enemyAi_NS {
  // TODO:
  // Need  to make both current pos and player pos not pointers and then pass in both in update and then return current pos
  class simpleEnemyMovement{
    public:
    Vector2 pos = {0.00f, 0.00f};
    Vector2 *currentPos = nullptr; 
    Vector2 playerPos = {0.00f,0.00f};
    Vector2 currentVelocity = {0.00f, 0.00f};
    Vector2 desiredVelocity = {0.00f, 0.00f};
    Vector2 defaultVelocity = {3.00f, 3.00f};
    Vector2 seekingForce = {0.00f, 0.00f};
    Vector2 seperationForce = {0.10f, 0.10f};
    std::vector<Rectangle> enemiesRects;
    std::vector<std::vector<int>> collisionIDs;
    std::vector<std::vector<int>> convertedCollisionIDs;
    AStar::CoordinateList path;
    AStar::Generator generator;
    bool shouldSeperate = false;
    //std::vector<Node> path;
  
 
    Vector2 nextPosition = {0.00f, 0.00f};
    int currentPathIndex = 0;
    bool isTakingAlternatePath = false;
    bool shouldTakeAlternatePath = false;
    simpleEnemyMovement(Vector2 *aPos, std::vector<Rectangle> someRects, std::vector<std::vector<int>> aCollisionIDs){ // a prefix for arg 
      currentPos = aPos;
      collisionIDs = aCollisionIDs;
      for(int i = 0; i < collisionIDs.size(); i++){
        std::vector<int> temp;
        for(int j = 0; j < collisionIDs[i].size(); j++){
          if(collisionIDs[i][j] == 0){
            temp.push_back(0);
          }
          else{
            temp.push_back(1);
          }
        }
        convertedCollisionIDs.push_back(temp);
      }
      enemiesRects = someRects;
    }
    simpleEnemyMovement(){};
    void update(std::vector<Rectangle> aEnemiesRects, Vector2 aPlayerPos){
      for(int j = 0; j < aEnemiesRects.size(); j++){
            std::clog << "other enemy pos = " << aEnemiesRects[j].x << " " << aEnemiesRects[j].y << std::endl;
         }
    
      enemiesRects = aEnemiesRects;
      playerPos = aPlayerPos; 
    }
    
   Vector2 aStarAlternativeMovement(Vector2 aNextPos){
     auto convertCoordinate = [](float x, float y) -> Vector2 {
         return {(x) / 16, (y ) / 16};
     };

     if(!isTakingAlternatePath){
         Vector2 start = convertCoordinate(currentPos->x, currentPos->y);
         Vector2 end = convertCoordinate(aNextPos.x, aNextPos.y);

         generator.setWorldSize({64, 64});
         for(int x = 0; x < 64; x++){
             for(int y = 0; y < 64; y++){
                 if(convertedCollisionIDs[y][x] == 1){
                     generator.addCollision({x, y});
                 }
             }
         }
         path = generator.findPath({(int)start.x, (int)start.y}, {(int)end.x, (int)end.y});
         for(int i = 0; i < path.size(); i++){
             std::clog << "path[" << i << "] = " << path[i].x << ", " << path[i].y << std::endl;
         }
         if(!path.empty()){
             isTakingAlternatePath = true;
         }
     }

     if(currentPathIndex >= path.size()){  
         isTakingAlternatePath = false;
         currentPathIndex = 0;
         return Vector2{-2, -2};
     }
     Vector2 nextPathVector = {0.00f, 0.00f};
     nextPathVector.x = path[currentPathIndex].x * 16 + 32;
      nextPathVector.y = path[currentPathIndex].y * 16 + 32;
   
    
     if(currentPos->x == nextPathVector.x && currentPos->y == nextPathVector.y){
         currentPathIndex++;
         // Avoid recursive call; use loop instead.
     } else {
         return nextPathVector;
     }

     return nextPathVector;
}

   
   void circlingMovement() {
    if (!currentPos) {
        std::clog << "currentPos is nullptr" << std::endl;
        return;
    }
    float maxSpeed = 2.0f; 
    float seekWeight = 1.0f;
    float separationWeight = 2.00f;
    float circlingWeight = 3.0f;
    float separationDistance = 8.00f;
    float circlingDistance = 1.0f;
    float stopThreshold = 5.0f;
    shouldSeperate = false;


    auto toGridIndex = [](float coord) -> int {
        return static_cast<int>((coord - 32) / 16);
    };

    desiredVelocity = {0.0f, 0.0f};

    if (!isTakingAlternatePath && !shouldTakeAlternatePath) {
        // Seek behavior
        seekingForce = Vector2Scale(Vector2Normalize(Vector2Subtract(playerPos, *currentPos)), maxSpeed);
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seekingForce, seekWeight));

        // Separation behavior
        for (Rectangle enemyRect : enemiesRects) { // fix this 
            Vector2 enemyPos = {enemyRect.x, enemyRect.y}; // EnemyRec is the same as CurrentPos therefore need to fix passing in the enemyRecs
            std::clog << "enemyRecPosition = " << enemyPos.x << " " << enemyPos.y << std::endl;
            std::clog << "current position = " << currentPos->x << " " << currentPos->y << std::endl;
            if (Vector2Distance(*currentPos, enemyPos) < separationDistance) {
                std::clog << "vector2Distance is = " << Vector2Distance(*currentPos, enemyPos) << std::endl;
                seperationForce = Vector2Add(seperationForce, Vector2Normalize(Vector2Subtract(*currentPos, enemyPos)));
                std::clog << "seperation force = " << seperationForce.x << " " << seperationForce.y << std::endl;
                shouldSeperate = true;
            }
        }
        if(shouldSeperate){
        seperationForce = Vector2Scale(Vector2Normalize(seperationForce), maxSpeed);
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seperationForce, separationWeight));
        }
        // Circling behavior 
        if (Vector2Distance(*currentPos, playerPos) < circlingDistance) {
            Vector2 toPlayer = Vector2Normalize(Vector2Subtract(playerPos, *currentPos));
            Vector2 perpendicular = { -toPlayer.y, toPlayer.x };
            Vector2 circlingForce = Vector2Scale(perpendicular, maxSpeed);
            desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(circlingForce, circlingWeight));
        }

        // Stopping close to the player
        if (Vector2Distance(*currentPos, playerPos) < stopThreshold) {
            desiredVelocity = {0.0f, 0.0f};
        }

        currentVelocity = Vector2Add(currentVelocity, Vector2Subtract(desiredVelocity, currentVelocity));
        nextPosition = Vector2Add(*currentPos, currentVelocity);

        int nextPositionXIndex = toGridIndex(nextPosition.x);
        int nextPositionYIndex = toGridIndex(nextPosition.y);

        // Boundary and collision check
        if (nextPositionXIndex >= 0 && nextPositionXIndex < 64 && 
            nextPositionYIndex >= 0 && nextPositionYIndex < 64) {
            if (collisionIDs[nextPositionYIndex][nextPositionXIndex] == 0) {
                *currentPos = Vector2Add(*currentPos, currentVelocity);
            } 
            else{
                currentVelocity = {0.00f, 0.00f};
                shouldTakeAlternatePath = true;
            }
        }
    } 
    else{
        shouldTakeAlternatePath = false;
        nextPosition = playerPos;
        Vector2 passInto  = {0.00f, 0.00f};
        if(playerPos.x - 16 < 0 || playerPos.y - 16 < 0 ){
          passInto = playerPos;
        } 
        else{
          passInto = {playerPos.x - 16, playerPos.y - 16};
        }
        nextPosition = aStarAlternativeMovement(passInto); 
        if (nextPosition.x == -2 && nextPosition.y == -2){
            std::clog << "next position return was -2, so END" << std::endl;
            isTakingAlternatePath = false;
        } 
        else{
           Vector2 direction = Vector2Subtract(nextPosition, *currentPos); // Calc Direction to next Pos
        Vector2 normalizedDirection = Vector2Normalize(direction); // Normalize Direction (values between 0 and 1)
        Vector2 movement = Vector2Scale(normalizedDirection, Vector2Length(defaultVelocity)); // Scale the direction by the default speed so it moves at the speed 
        *currentPos = Vector2Add(*currentPos, movement); // Update Pos
      // Check if we overshot position
         if(Vector2Distance(*currentPos, nextPosition) < 4.0f){  
        *currentPos = nextPosition;
        } 
        }

        if (nextPosition.x == -1 && nextPosition.y == -1){
            std::clog << "next position return was -1, so BAD" << std::endl;
        }
        
    }



   }
    };
};
#endif