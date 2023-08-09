#ifndef enemyAi_h
#define enemyAi_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include <vector>
#include "raymath.h"
#include <memory> 
#include "frameUtility.hpp"  
namespace enemyAi_NS {
  class simpleEnemyMovement{
    public:
    Vector2 pos = {0.00f, 0.00f};
    Vector2 *currentPos; 
    Vector2 *playerPos;
    Vector2 currentVelocity = {0.00f, 0.00f};
    Vector2 desiredVelocity = {0.00f, 0.00f};
    Vector2 seekingForce = {0.00f, 0.00f};
    Vector2 seperationForce = {0.00f, 0.00f};
    std::vector<Rectangle> enemiesRects;
    simpleEnemyMovement(Vector2 *aPos, Vector2 *aPlayerPos, std::vector<Rectangle>){ // a prefix for arg 
      currentPos = aPos;
      playerPos = aPlayerPos;
      
    }
    void update(std::vector<Rectangle> aEnemiesRects){
      enemiesRects = aEnemiesRects;
    }
   void circlingMovement() {
    float maxSpeed = 2.0f; // 
    float seekWeight = 1.0f; // 
    float separationWeight = 2.0f; //  
    float circlingWeight = 3.0f; //
    float separationDistance = 10.0f; // 
    float circlingDistance = 30.0f; //

    // Seek behavior
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
    *currentPos = Vector2Add(*currentPos, currentVelocity); // Update the position
}


    };
};
#endif