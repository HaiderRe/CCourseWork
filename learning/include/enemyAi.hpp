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
//#include "aStar.hpp"
namespace enemyAi_NS {
  // TODO:
  // Need  to make both current pos and player pos not pointers and then pass in both in update and then return current pos
  class simpleEnemyMovement{
    public:
    Vector2 pos = {0.00f, 0.00f};
    Vector2 *currentPos = nullptr; 
    Vector2 *playerPos = nullptr;
    Vector2 currentVelocity = {0.00f, 0.00f};
    Vector2 desiredVelocity = {0.00f, 0.00f};
    Vector2 defaultVelocity = {3.00f, 3.00f};
    Vector2 seekingForce = {0.00f, 0.00f};
    Vector2 seperationForce = {0.00f, 0.00f};
    std::vector<Rectangle> enemiesRects;
    std::vector<std::vector<int>> collisionIDs;
  //  std::vector<Node> path;
    Vector2 nextPosition = {0.00f, 0.00f};
    int currentPathIndex = 0;
    bool isTakingAlternatePath = false;
    simpleEnemyMovement(Vector2 *aPos, Vector2 *aPlayerPos, std::vector<Rectangle> someRects, std::vector<std::vector<int>> aCollisionIDs){ // a prefix for arg 
      currentPos = aPos;
      playerPos = aPlayerPos;
      collisionIDs = aCollisionIDs;
      enemiesRects = someRects;
    }
    simpleEnemyMovement(){};
    void update(std::vector<Rectangle> aEnemiesRects){
      enemiesRects = aEnemiesRects;
    }
    /*
    Vector2 aStarAlternativeMovement(Vector2 aNextPos){ // Takes in the next position the enemy is going to move to and returns the next position
     if(isTakingAlternatePath == false){
       Node start = {(int)currentPos->x / 16, (int)currentPos->y / 16, 0, 0, 0, 0, 0};
        Node end = {(int)aNextPos.x / 16, (int)aNextPos.y / 16, 0, 0, 0, 0, 0};
        path = Cordinate::aStar(start, end);
       if(path.size() > 0){
         isTakingAlternatePath = true;
       }
       return Vector2{-1, -1};
     }
     else{
      if(currentPathIndex >= path.size()){
        isTakingAlternatePath = false;
        currentPathIndex = 0;
        return Vector2{-2, -2};
      }
      float pathX = path[currentPathIndex].x * 16;
      float pathY = path[currentPathIndex].y * 16;
      Vector2 nextPathVector =  Vector2{pathX, pathY};
    
      if(currentPos->x == nextPathVector.x && currentPos->y == nextPathVector.y){
        currentPathIndex++;
        if(currentPathIndex >= path.size()){
          isTakingAlternatePath = false;
          currentPathIndex = 0;
          return Vector2{-1, -1};
        }
        return aStarAlternativeMovement(aNextPos);
      }
      else{
        return nextPathVector;
      }
      return nextPathVector;
     }
   }
   */
   void circlingMovement() {
    if (currentPos == nullptr || playerPos == nullptr) {
    std::clog << "currentPos or playerPos is nullptr" << std::endl;
    return;
    }
    std::clog << playerPos << std::endl;
    return;
    float maxSpeed = 2.0f; // 
    float seekWeight = 1.0f; // 
    float separationWeight = 2.0f; //  
    float circlingWeight = 3.0f; //
    float separationDistance = 32.0f; // 
    float circlingDistance = 32.0f; //

    // Seek behavior
    if(!isTakingAlternatePath){
    seekingForce = Vector2Scale(Vector2Normalize(Vector2Subtract(*playerPos, *currentPos)), maxSpeed);
    desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seekingForce, seekWeight));

    // Separation behavior
    for (Rectangle enemyRect : enemiesRects) {
        Vector2 enemyPos = {enemyRect.x, enemyRect.y};
        if (Vector2Distance(*currentPos, enemyPos) < separationDistance) {
            seperationForce = Vector2Add(seperationForce, Vector2Normalize(Vector2Subtract(*currentPos, enemyPos)));
        }
    }
    seperationForce = Vector2Scale(Vector2Normalize(seperationForce), maxSpeed);
    desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seperationForce, separationWeight));

    // Circling behavior 
    if (Vector2Distance(*currentPos, *playerPos) < circlingDistance) {
        Vector2 toPlayer = Vector2Normalize(Vector2Subtract(*playerPos, *currentPos));
        Vector2 perpendicular = { -toPlayer.y, toPlayer.x }; // 90-degree rotation
        Vector2 circlingForce = Vector2Scale(perpendicular, maxSpeed);
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(circlingForce, circlingWeight));
    }

    
    currentVelocity = desiredVelocity;  // Apply the force to the enemy
    nextPosition = Vector2Add(*currentPos, currentVelocity); // Calculate the next position
    int xIndex = (int)nextPosition.x / 16; // Calculate the tile index
    int yIndex = (int)nextPosition.y / 16;
    if(yIndex < collisionIDs.size() && xIndex < collisionIDs[yIndex].size() && collisionIDs[yIndex][xIndex] == 0){
    *currentPos = Vector2Add(*currentPos, currentVelocity); // Update position
    }
    else{
      currentVelocity = {0.00f, 0.00f};
      isTakingAlternatePath = true;
     }
    }
    else{
      // Next position being passed in may be an obstacle so the function will never work as it will try to put the enemy into an obstacle which it can't do
      // As we only enter this if statement when there is an obstacle
      // Could instead pass in player position
  //    nextPosition = aStarAlternativeMovement(*playerPos); 
    nextPosition = Vector2{1, -1};
      if(nextPosition.x != -2 && nextPosition.y != -2){
        *currentPos = nextPosition;
        std::clog << "next position return was -2, so END" << std::endl;
      }
      if(nextPosition.x == -1 && nextPosition.y == -1){
        std::clog << "next position return was -1, so BAD" << std::endl;
      }
      // Fun maths :)
      Vector2 direction = Vector2Subtract(nextPosition, *currentPos); // Calc Direction to next Pos
      Vector2 normalizedDirection = Vector2Normalize(direction); // Normalize Direction (values between 0 and 1)
      Vector2 movement = Vector2Scale(normalizedDirection, Vector2Length(defaultVelocity)); // Scale the direction by the default speed so it moves at the speed 
      *currentPos = Vector2Add(*currentPos, movement); // Update Pos
      // Check if we overshot position
    if(Vector2Distance(*currentPos, nextPosition) < 1.0f){  
        *currentPos = nextPosition;
    }  
   }

   }
    };
};
#endif