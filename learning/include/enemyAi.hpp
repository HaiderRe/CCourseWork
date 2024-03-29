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
#include <random> 
#include <cstdlib>   
#include <ctime>    
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
    float circlingDistance = 32.0f; // moved for other methods to use 
    float stopThreshold = 48.0f; // moved for other methods to use 
    Vector2 stopOffsetCircle = {0.00f, 0.00f};
    Vector2 circlingOffsetCircle = {0.00f, 0.00f}; 
    Vector2 circleOffset = {0.00f, 0.00f};
    Vector2 seekOffset = {0.00f, 0.00f}; // trig 
    bool shouldSeperate = false;
    bool validOffset = false;
    std::string* currentState; //idle, attack, move, dead, hurt (?)
    //std::vector<Node> path;
  void NewchooseCirclePoint() {
    // Center of the circles
 //   float circleCenterX = playerPos.x + 32.0f;
   // float circleCenterY = playerPos.y + 32.0f;
      float circleCenterX = 32.0f;
      float circleCenterY = 32.0f;
    float theta = ((float)rand() / RAND_MAX) * 2 * PI;
    float stopOffsetX = stopThreshold * cos(theta);
    float stopOffsetY = stopThreshold * sin(theta);
    float circlingOffsetX = circlingDistance * cos(theta);
    float circlingOffsetY = circlingDistance * sin(theta);
    stopOffsetCircle = {circleCenterX + stopOffsetX, circleCenterY + stopOffsetY};
    circlingOffsetCircle = {circleCenterX + circlingOffsetX, circleCenterY + circlingOffsetY};
    
}


   float quadFormula(float a, float b, float c){
    return  (-b + sqrt(b*b - 4 * a * c)/(2*a)); // quadratic Formula
   }
    Vector2 nextPosition = {0.00f, 0.00f};
    int currentPathIndex = 0;
    bool isTakingAlternatePath = false;
    bool shouldTakeAlternatePath = false;
    void chooseCirclePoint() {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * PI; 
    stopOffsetCircle.x = stopThreshold * cos(angle);
    stopOffsetCircle.y = stopThreshold * sin(angle);
    circlingOffsetCircle.x = circlingDistance * cos(angle);
    circlingOffsetCircle.y = circlingDistance * sin(angle);
   
}

    void OldChooseCirclePoint(){
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
             int lowerBound = 0;     
           int upperBound = 360;   

    // Generate a random number within the range
    int rotationOffset = rand() % (upperBound - lowerBound + 1) + lowerBound;

        float x = 0.00f;
        float y = 0.00f;
        x = (circlingDistance * cos(rotationOffset));
        y = (circlingDistance * sin(rotationOffset));
        circleOffset = {x, y};
        float x2 = 0.00f;
        float y2 = 0.00f;
        x2 = (stopThreshold * cos(rotationOffset));
        y2 = (stopThreshold * sin(rotationOffset));
        seekOffset = {x2, y2};

    }
    void testingDrawDebug(){
    Vector2 currentSeekOffset = Vector2Add(stopOffsetCircle, playerPos);
    Vector2 CurrentCircleOffset = Vector2Add(circlingOffsetCircle, playerPos);

       // DrawCircle(playerPos.x, playerPos.y, circlingDistance, RED);
       DrawCircle(CurrentCircleOffset.x, CurrentCircleOffset.y, 1.5f, GREEN);
       // DrawCircle(playerPos.x,playerPos.y, stopThreshold, RED);
      //  DrawCircle(playerPos.x + 32, playerPos.y + 32, stopThreshold, PURPLE);
        //DrawLine(playerPos.x, playerPos.y, CurrentCircleOffset.x, CurrentCircleOffset.y, PURPLE);
        DrawLine(0,0, playerPos.x, playerPos.y, DARKBLUE);
        DrawLine(playerPos.x, playerPos.y, currentSeekOffset.x, currentSeekOffset.y, GREEN);
        DrawCircle(currentSeekOffset.x, currentSeekOffset.y, 1.0f, BLACK);
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
    simpleEnemyMovement(Vector2 *aPos, std::vector<Rectangle> someRects, std::vector<std::vector<int>> aCollisionIDs, float aCirclingDistance, float aStopThreshold){ // a prefix for arg 
      currentPos = aPos;
      collisionIDs = aCollisionIDs;
      circlingDistance = aCirclingDistance;
      aStopThreshold = stopThreshold;
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

   bool collisionCheck(Vector2 aPoint){
    if(aPoint.x / 16 < 0 || aPoint.y / 16 < 0){
      return true;
    }
    if(aPoint.x / 16 > 64 || aPoint.y / 16 > 64){
      return true;
    }
    if(convertedCollisionIDs[floor(aPoint.y / 16)][floor(aPoint.x / 16)] == 1){
      return true;
    }
    return false;
   }
   void moveToNewPos(Vector2 aNewPos){
     *currentPos = aNewPos;
   }

   void circlingMovement() {
    if(*currentState == "attack" || *currentState == "dead"){
     // std::clog << "currentState is " << *currentState << std::endl;
      return;
    }
    if(playerPos.x < -1){
      *currentState = "idle";
      return;
    }
    *currentState = "move";
    if (!currentPos) {
        return;
    }
    
    if(validOffset == false){
        NewchooseCirclePoint();    
        validOffset = true;
    }
    if(IsKeyPressed(KEY_F) && false){ //Stop
        NewchooseCirclePoint();
        moveToNewPos(Vector2Add(stopOffsetCircle, playerPos));
    }
    Vector2 currentSeekOffset = Vector2Add(stopOffsetCircle, playerPos);
    Vector2 CurrentCircleOffset = Vector2Add(circlingOffsetCircle, playerPos);
    //if(collisionCheck(currentSeekOffset) || collisionCheck(CurrentCircleOffset) ){
      if(false){
        int x = 0;
        while(collisionCheck(currentSeekOffset) || collisionCheck(CurrentCircleOffset)){
            x++;
            NewchooseCirclePoint();
            currentSeekOffset = Vector2Add(stopOffsetCircle, playerPos);
            CurrentCircleOffset = Vector2Add(circlingOffsetCircle, playerPos);
            if(x > 30){
                break; 
            }
        }
        moveToNewPos(Vector2Add(stopOffsetCircle, playerPos));

    }

    
    float maxSpeed = 2.0f; 
    float seekWeight = 1.0f;
    float separationWeight = 2.00f;
    float circlingWeight = 2.20f;
    float separationDistance = 2.00f;
    // circlingDistance = 1.0f;
    // stopThreshold = 5.0f;

    shouldSeperate = false;


    auto toGridIndex = [](float coord) -> int {
        return static_cast<int>((coord - 32) / 16);
    };

    desiredVelocity = {0.0f, 0.0f};

    if (!isTakingAlternatePath && !shouldTakeAlternatePath) {
        // Seek behavior
        
        // Separation behavior
        for (Rectangle enemyRect : enemiesRects) { // 
            Vector2 enemyPos = {enemyRect.x, enemyRect.y}; //
            if (Vector2Distance(*currentPos, enemyPos) < separationDistance) {
                seperationForce = Vector2Add(seperationForce, Vector2Normalize(Vector2Subtract(*currentPos, enemyPos)));
                shouldSeperate = true;
            }
        }
        
        // Circling behavior 
          bool isStopping = false;
        
        Vector2 circlingForce = {0.00f};
       if (Vector2Distance(*currentPos, Vector2Add(playerPos, Vector2{32,32})) < circlingDistance) {
         
            Vector2 toPlayer = Vector2Normalize(Vector2Subtract(CurrentCircleOffset, *currentPos));
            Vector2 perpendicular = { -toPlayer.y, toPlayer.x };
             circlingForce = Vector2Scale(perpendicular, maxSpeed);
            desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(circlingForce, circlingWeight));
            isStopping = true;
            
        }
      
        // Stopping close to the player
        if (Vector2Distance(*currentPos, Vector2Add(playerPos ,Vector2{32,32 })) <= stopThreshold) {
            desiredVelocity = {0.0f, 0.0f};
            isStopping = true;
            *currentState = "attack";
        }
        float tolerance = 1.0f;
        if (Vector2Distance(*currentPos, Vector2Add(playerPos ,Vector2{32,32 })) <= stopThreshold + tolerance) {
        desiredVelocity = {0.0f, 0.0f};
        isStopping = true;
       }
       if(Vector2Distance(*currentPos, CurrentCircleOffset) > 4.00f && isStopping){
        Vector2 aForce = Vector2Scale(Vector2Normalize(Vector2Subtract(CurrentCircleOffset, *currentPos)), maxSpeed);
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(aForce, 1.00f));
       }
       if(shouldSeperate && isStopping == false){
        seperationForce = Vector2Scale(Vector2Normalize(seperationForce), maxSpeed);
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seperationForce, separationWeight));
        
        }
        if(isStopping == false){
        seekingForce = Vector2Scale(Vector2Normalize(Vector2Subtract(currentSeekOffset, *currentPos)), maxSpeed);
    
        desiredVelocity = Vector2Add(desiredVelocity, Vector2Scale(seekingForce, seekWeight));
        
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
                //currentVelocity = {0.00f, 0.00f};
                //shouldTakeAlternatePath = true;
                slidingMovement();
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

        
        
    }
    


   }
      void slidingMovement(){
    auto toGridIndex = [](float coord) -> int {
        return static_cast<int>((coord - 32) / 16);
    };
Vector2 nextPosX = Vector2Add(*currentPos, {currentVelocity.x, 0});
Vector2 nextPosY = Vector2Add(*currentPos, {0, currentVelocity.y});
int nextPositionXIndex = toGridIndex(nextPosX.x);
int nextPositionYIndex = toGridIndex(nextPosY.y);
bool xCollides = (nextPositionXIndex >= 0 && nextPositionXIndex < 64 &&  collisionIDs[nextPositionYIndex][nextPositionXIndex] != 0);
nextPositionXIndex = toGridIndex(nextPosY.x);
nextPositionYIndex = toGridIndex(nextPosY.y);

bool yCollides = (nextPositionYIndex >= 0 && nextPositionYIndex < 64 && collisionIDs[nextPositionYIndex][nextPositionXIndex] != 0);
if (xCollides && yCollides) {
    int diagXIndex = toGridIndex(Vector2Add(*currentPos, currentVelocity).x);
    int diagYIndex = toGridIndex(Vector2Add(*currentPos, currentVelocity).y);
    bool diagCollides = (diagXIndex >= 0 && diagXIndex < 64 && diagYIndex >= 0 && diagYIndex < 64 && collisionIDs[diagYIndex][diagXIndex] != 0);
    if (!diagCollides){
        *currentPos = Vector2Add(*currentPos, currentVelocity);
        return;
    }
}
if (!xCollides && !yCollides){
    *currentPos = Vector2Add(*currentPos, currentVelocity);
} 
else {
    if (xCollides) {
        if(currentPos->y  < playerPos.y){
          currentVelocity.y += abs(currentVelocity.x);
        }
        else{
          currentVelocity.y += -1 * abs(currentVelocity.x);
        }
        currentVelocity.x = 0;
    }
    if (yCollides) {
       if(currentPos->x < playerPos.x){
          currentVelocity.x += abs(currentVelocity.y);
        }
        else{
          currentVelocity.x += -1 * abs(currentVelocity.y);
        }        currentVelocity.y = 0;
    }
    *currentPos = Vector2Add(*currentPos, currentVelocity);
}

   }
    };
     class DirectApproachEnemy {
    private:
        Vector2* currentPos;
        Vector2 playerPos;
        Vector2 currentVelocity;
        float attackRange;
        float speed;
        std::string currentState; // "move", "attack", "idle"
        std::vector<std::vector<int>> collisionIDs;

        void slidingMovement(){
    auto toGridIndex = [](float coord) -> int {
        return static_cast<int>((coord - 32) / 16);
    };
Vector2 nextPosX = Vector2Add(*currentPos, {currentVelocity.x, 0});
Vector2 nextPosY = Vector2Add(*currentPos, {0, currentVelocity.y});
int nextPositionXIndex = toGridIndex(nextPosX.x);
int nextPositionYIndex = toGridIndex(nextPosY.y);
bool xCollides = (nextPositionXIndex >= 0 && nextPositionXIndex < 64 &&  collisionIDs[nextPositionYIndex][nextPositionXIndex] != 0);
nextPositionXIndex = toGridIndex(nextPosY.x);
nextPositionYIndex = toGridIndex(nextPosY.y);

bool yCollides = (nextPositionYIndex >= 0 && nextPositionYIndex < 64 && collisionIDs[nextPositionYIndex][nextPositionXIndex] != 0);
if (xCollides && yCollides) {
    int diagXIndex = toGridIndex(Vector2Add(*currentPos, currentVelocity).x);
    int diagYIndex = toGridIndex(Vector2Add(*currentPos, currentVelocity).y);
    bool diagCollides = (diagXIndex >= 0 && diagXIndex < 64 && diagYIndex >= 0 && diagYIndex < 64 && collisionIDs[diagYIndex][diagXIndex] != 0);
    if (!diagCollides){
        *currentPos = Vector2Add(*currentPos, currentVelocity);
        return;
    }
}
if (!xCollides && !yCollides){
    *currentPos = Vector2Add(*currentPos, currentVelocity);
} 
else {
    if (xCollides) {
        if(currentPos->y  < playerPos.y){
          currentVelocity.y += abs(currentVelocity.x);
        }
        else{
          currentVelocity.y += -1 * abs(currentVelocity.x);
        }
        currentVelocity.x = 0;
    }
    if (yCollides) {
       if(currentPos->x < playerPos.x){
          currentVelocity.x += abs(currentVelocity.y);
        }
        else{
          currentVelocity.x += -1 * abs(currentVelocity.y);
        }        currentVelocity.y = 0;
    }
    *currentPos = Vector2Add(*currentPos, currentVelocity);
}

   }
    public:
        DirectApproachEnemy(Vector2* aPos, float aAttackRange, float aSpeed, std::vector<std::vector<int>> aCollisionIDs)  : currentPos(aPos), attackRange(aAttackRange), speed(aSpeed), collisionIDs(aCollisionIDs), currentState("move") {}
        DirectApproachEnemy(){}
        float restTime = 0.20f; // 
       float currentRestTime = 0.00f;
       bool *isAttacking;
       float attackTime = 8.00f;
        float currentAttackTime = 0.00f;
        bool attackDone = false;
        void update(Vector2 aPlayerPos) {
          playerPos = aPlayerPos;
        }
     std::string movement() {
    auto toGridIndex = [](float coord) -> int {
        return static_cast<int>((coord - 32) / 16);
    };

    if (currentRestTime > 0) {
        currentRestTime -= GetFrameTime(); 
        return currentState;
    }

    float buffer = 3.00f; 
    float attackBuffer = 112.0f; //

    float distanceToPlayer = Vector2Distance(*currentPos, playerPos);
    *isAttacking = false;
    if(attackDone = true){
      *isAttacking = false;
      currentState = "idle";
    }
    if (distanceToPlayer <= attackRange + attackBuffer && currentAttackTime <= 0) {
        currentState = "attack";
        attackDone = false;
    
            *isAttacking = true;
            currentAttackTime = attackTime;
    } 
    if(currentAttackTime > 0){
      currentAttackTime -= GetFrameTime();
      if(currentAttackTime <= 0){
        currentAttackTime = 0;
      }
    }
   if (distanceToPlayer >= attackRange) {
        currentState = "move";
    } else {
        return currentState;
    }

    Vector2 newVelocity = {0.0f, 0.0f};

    if (currentState == "move" ) {
        Vector2 direction = Vector2Subtract(playerPos, *currentPos);
        newVelocity = Vector2Scale(Vector2Normalize(direction), speed);
    } 
    else if (currentState == "attack" && false) {
        Vector2 direction = Vector2Subtract(*currentPos, playerPos);
        newVelocity = Vector2Scale(Vector2Normalize(direction), speed);
    }

    float velocityChangeMagnitude = Vector2Length(Vector2Subtract(newVelocity, currentVelocity));
    float velocityChangeThreshold = 4.00f; // change

    if (velocityChangeMagnitude > velocityChangeThreshold || velocityChangeMagnitude > 4) {
        currentRestTime = restTime; // 
        return currentState;
    }

    currentVelocity = newVelocity;

    Vector2 nextPos = Vector2Add(*currentPos, currentVelocity);
    int nextPositionXIndex = toGridIndex(nextPos.x);
    int nextPositionYIndex = toGridIndex(nextPos.y);

    if (nextPositionXIndex >= 0 && nextPositionXIndex < 64 &&  nextPositionYIndex >= 0 && nextPositionYIndex < 64) {
        if (collisionIDs[nextPositionYIndex][nextPositionXIndex] != 0) {
            slidingMovement();
        } else {
            *currentPos = nextPos;
        }
    }
    return currentState;
}


    };
};
#endif