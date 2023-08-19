#ifndef enemyAiNew_h
#define enemyAiNew_h
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
#include <random> 
#include <cstdlib>   
#include <ctime>    
namespace enemyAiNew_NS {
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
    std::vector<Rectangle> enemiesRects;
    std::vector<std::vector<int>> collisionIDs;
    std::vector<std::vector<int>> convertedCollisionIDs;
    AStar::CoordinateList path;
    AStar::Generator generator;
    Vector2 nextPosition = {0.00f, 0.00f};
    bool shouldSeperate = false;
    bool validOffset = false;
    bool isTakingAlternatePath = false;
    bool shouldTakeAlternatePath = false;
    std::string stateMachine = "IDLE"; // IDLE, ATTACK, MOVE, DEAD
    int currentIndex = 0;
    std::vector<Vector2> pathVector2;
    //std::vector<Node> path;
  void NewchooseCirclePoint() {
    // Center of the circles
 //   float circleCenterX = playerPos.x + 32.0f;
   // float circleCenterY = playerPos.y + 32.0f;
      float circleCenterX = 32.0f;
      float circleCenterY = 32.0f;
    float theta = ((float)rand() / RAND_MAX) * 2 * PI;
/*  float stopOffsetX = stopThreshold * cos(theta);
    float stopOffsetY = stopThreshold * sin(theta);
    float circlingOffsetX = circlingDistance * cos(theta);
    float circlingOffsetY = circlingDistance * sin(theta);
    stopOffsetCircle = {circleCenterX + stopOffsetX, circleCenterY + stopOffsetY};
    circlingOffsetCircle = {circleCenterX + circlingOffsetX, circleCenterY + circlingOffsetY};
    std::clog << "stopOffsetCircle Values = " << stopOffsetCircle.x << " " << stopOffsetCircle.y << std::endl;
    std::clog << "circlingOffsetCircle Values = " << circlingOffsetCircle.x << " " << circlingOffsetCircle.y << std::endl;
    */
}


    

    void testingDrawDebug(){
    }
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
      enemiesRects = aEnemiesRects;
      playerPos = aPlayerPos; 
    }
    
   std::vector<Vector2> aStarAlternativeMovement(Vector2 aNextPos){
     auto convertCoordinate = [](float x, float y) -> Vector2 {
        float x1 = floor(x / 16);
        float y1 = floor(y/16);
         return {x1, y1};
     };
     
     if(shouldTakeAlternatePath){
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
             pathVector2.push_back(Vector2{(float)path[i].x, (float)path[i].y});
         }
         if(!path.empty()){
             isTakingAlternatePath = true;
         }
     }
     return pathVector2;
}

   bool collisionCheck(Vector2 aPoint){
    int xIndex = floor(aPoint.x / 16);
    int yIndex = floor(aPoint.y  / 16);

    if(xIndex < 0 || yIndex < 0 || xIndex > 64 || yIndex > 64){
        return true;
    }
    if(convertedCollisionIDs[yIndex][xIndex] == 1){
    std::clog << "enemy collision " << std::endl;
    shouldTakeAlternatePath = true;
        return true;
    }
    return false;
}
Vector2 separationForce(Rectangle currentEnemy) {
    const float desiredSeparation = 4.0f;
    Vector2 force = {0.0f, 0.0f};
    int count = 0;

    for (const auto& otherEnemy : enemiesRects) {
        float distance = Vector2Distance(
            {currentEnemy.x + currentEnemy.width/2, currentEnemy.y + currentEnemy.height/2},
            {otherEnemy.x + otherEnemy.width/2, otherEnemy.y + otherEnemy.height/2}
        );

        if ((distance > 0) && (distance < desiredSeparation)) {
            Vector2 direction = {
                currentEnemy.x + currentEnemy.width/2 - otherEnemy.x - otherEnemy.width/2,
                currentEnemy.y + currentEnemy.height/2 - otherEnemy.y - otherEnemy.height/2
            };

            force.x += direction.x;
            force.y += direction.y;
            count++;
        }
    }

    if (count > 0) {
        force.x /= count;
        force.y /= count;
    }

    return force;
}

Vector2 speedRatio(Vector2 aPlayerPos){
    float xDistance = aPlayerPos.x - currentPos->x;
    float yDistance = aPlayerPos.y - currentPos->y;

    if (xDistance == 0.0f) {
        return Vector2{0.0f, (yDistance > 0 ? defaultVelocity.y : -defaultVelocity.y)};
    }

    float angle = atan(yDistance / xDistance);
    float xSpeed = defaultVelocity.x * cos(angle);
    float ySpeed = defaultVelocity.y * sin(angle);

    xSpeed = (xDistance > 0) ? abs(xSpeed) : -abs(xSpeed);
    ySpeed = (yDistance > 0) ? abs(ySpeed) : -abs(ySpeed);

    return Vector2{xSpeed, ySpeed};
}

bool shouldMove(Vector2 playerPosCenter){
    if(Vector2Distance(*currentPos, playerPosCenter) < 48.00f){
        // stateMachine = "ATTACK"; // Not Implemented
        return false;
    }
    Vector2 currentSpeed = speedRatio(playerPosCenter);
    Vector2 nextPosition = {currentPos->x + currentSpeed.x, currentPos->y + currentSpeed.y};
    bool x = !collisionCheck(nextPosition);
    return x;
}
void circlingMovement(){
  movement();
}
void movement(){
    stateMachine = "MOVE";
    Vector2 playerPosCenter = {playerPos.x + 32, playerPos.y + 32};

    if(shouldMove(playerPosCenter) && shouldTakeAlternatePath == false && isTakingAlternatePath == false){
        Vector2 currentSpeed = speedRatio(playerPosCenter);
        Rectangle currentEnemyRect = {currentPos->x, currentPos->y, 32, 32};
        
        Vector2 separation = separationForce(currentEnemyRect);
        currentSpeed.x += separation.x;
        currentSpeed.y += separation.y;
        currentPos->x += currentSpeed.x;
        currentPos->y += currentSpeed.y;
    }
    else{
        if(shouldTakeAlternatePath && isTakingAlternatePath == false){
        pathVector2 = aStarAlternativeMovement(playerPosCenter);
        isTakingAlternatePath = true;
        shouldTakeAlternatePath = false;
        }   
        if(!pathVector2.empty() && currentIndex < pathVector2.size()){
            nextPosition = pathVector2[currentIndex];
            pathVector2.erase(pathVector2.begin());
            isTakingAlternatePath = true;
            currentPos->x = nextPosition.x * 16;
            currentPos->y = nextPosition.y * 16;
            currentIndex++;
        }
        else {
            shouldTakeAlternatePath = false;
            isTakingAlternatePath = false;
            currentIndex = 0;
        }
    }
}





   
    };
};
#endif