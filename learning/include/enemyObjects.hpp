#ifndef enemyObjects_h
#define enemyObjects_h
#include <iostream> 
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "player_objects.hpp"
#include "projectile.hpp"
#include "frameUtility.hpp"
#include "enemyAi.hpp"
#include "enemyAiNew.hpp"
#include "slimeAttack.hpp"
#include <memory>
namespace enemyObjects_NS{
    class basicEnemy{
        public:
        int health = 120;
        int dWidth = 32;
        int dHeight = 32;
        int direction = 0; // 0 = up, 1 = left, 2 = right, 3 = down (Different to other textures)
        float speedY = 1.0f;
        float speedX = 1.0f;
        Vector2 destRecPos = {0.0f,0.0f};
        Rectangle frameRec = {0.0f, 0.0f, 32, 32};
        Rectangle destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
        Texture2D enemyTexture = LoadTexture("Assets/enemy/blueSlime.png");
        player_objects::player *thePlayer; // Add player else where
        std::vector<Rectangle> otherEnemyRects; 
        frameUtility_NS::frameUtility enemyFrameUtility;
        std::vector<std::vector<int>> collisionIDs;
        basicEnemy(Vector2 spawnPointPos){
            destRecPos = spawnPointPos;
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility = frameUtility_NS::frameUtility(enemyTexture, 6, 144, 144, 64, 64, direction);
        }
        basicEnemy(Vector2 spawnPointPos, std::string texturePath, std::vector<std::vector<int>> aCollisionIDs){
            destRecPos = spawnPointPos;
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            UnloadTexture(enemyTexture);
            enemyTexture = LoadTexture(("Assets/enemy/" + texturePath).c_str());
            enemyFrameUtility = frameUtility_NS::frameUtility(enemyTexture, 6, 144, 144, 64, 64, direction);
            collisionIDs = aCollisionIDs;
        }
        basicEnemy(){
            std::clog << "In basicEnemy constructor" << std::endl;
            enemyFrameUtility = frameUtility_NS::frameUtility(enemyTexture, 6, 144, 144, 64, 64, direction);
        }
        void deload(){
            std::clog << "In basicEnemy deload" << std::endl;
        }
        virtual void movement(){
            //Move towards player
            if(destRecPos.x < 0 || destRecPos.x > 4000 || destRecPos.y < 0 || destRecPos.y > 4000){
                health = 0;
                return;
            }
            std::clog << "player's pos including offset = " << thePlayer->destRecPos.x + (thePlayer->width/2) << " " << thePlayer->destRecPos.y + (thePlayer->height/2) << std::endl;
            std::clog << "enemy's pos including offset = " << destRecPos.x + dWidth/2 << " " << destRecPos.y + dHeight/2 << std::endl;
            if(destRecPos.x + dWidth/2 < thePlayer->destRecPos.x + (thePlayer->width/2)){
                destRecPos.x += speedX;
                direction = 2;
            }
            if(destRecPos.x + dWidth/2> thePlayer->destRecPos.x + (thePlayer->width/2) ){
                destRecPos.x -= speedX;
                direction = 1;
            }
            if(destRecPos.y + dWidth/2 < thePlayer->destRecPos.y + (thePlayer->height/2)){
                destRecPos.y += speedY;
                direction = 0;
            }
            if(destRecPos.y + dWidth/2> thePlayer->destRecPos.y + (thePlayer->height/2)){
                destRecPos.y -= speedY;
                direction = 3;
            }
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
           
        }
        virtual void draw(){
            enemyFrameUtility.draw();
            DrawLine(destRecPos.x, destRecPos.y, otherEnemyRects[0].x, otherEnemyRects[0].y, RED);
            DrawText(std::to_string(Vector2Distance(destRecPos, Vector2{otherEnemyRects[0].x, otherEnemyRects[0].y})).c_str(), destRecPos.x, destRecPos.y - 10, 12, BLACK);
            
          //  std::clog << "Drawing enemy " << std::endl;
           // enemyProjectile.draw();
        }
        virtual void update(){
            movement();
            enemyFrameUtility.destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility.direction = direction;
           // shootLogic();
        }
        virtual void unloadTexture(){}
    };
    class slimeEnemy : public basicEnemy{
        public:
       // enemyAi_NS::simpleEnemyMovement slimeEnemyMovement;
       std::string stateMachineMemAcc = "idle";
       std::string* stateMachine; // idle, attack, move, death, hurt(?),
       enemyAi_NS::simpleEnemyMovement slimeEnemyMovement;
       slimeAttack_NS::Attack slimeAttack;
             slimeEnemy(Vector2 aPos, std::string path, std::vector<std::vector<int>> aCollisionIDs): basicEnemy(aPos, path, aCollisionIDs) {
                slimeEnemyMovement = enemyAi_NS::simpleEnemyMovement(&destRecPos,  otherEnemyRects, aCollisionIDs);
                stateMachine = &stateMachineMemAcc;
                slimeEnemyMovement.currentState = stateMachine;
                slimeAttack = slimeAttack_NS::Attack(&destRecPos);
                slimeAttack.currentState = stateMachine;

         }
         void movement() override{
            slimeEnemyMovement.circlingMovement();
         }
         void directionCalc(){
            if(destRecPos.x < thePlayer->destRecPos.x + 32){
                direction = 2;
            }
            else{
                direction = 1;
            }
            if(*stateMachine == "attack"){
                return;
            }
            if( destRecPos.y + 32 < thePlayer->destRecPos.y + 32 ) // cjamge cjpde
            {
                direction = 0;
            }
            else if(destRecPos.y - 32 > thePlayer->destRecPos.y + 32){
                direction = 3;
            }
         }
         void checkAttackHit(){
            if(slimeAttack.hitPlayer == true){
                thePlayer->takeDamage(1.00f);
                slimeAttack.hitPlayer = false;
            }
         }
         void update() override{ // overriding update() from basicEnemy
         
            enemyFrameUtility.destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility.direction = direction;
            slimeEnemyMovement.update(otherEnemyRects, thePlayer->destRecPos);
             movement();
            slimeAttack.update(thePlayer->destRecPos, {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)}, direction);
            directionCalc();
            checkAttackHit();
         }
         void unloadTexture() override{
             UnloadTexture(slimeAttack.attackTexture);
         }
         void draw() override{
            if(*stateMachine == "attack"){
                slimeAttack.drawAttack();
            }
            else{
            enemyFrameUtility.draw();
            }
          //  DrawLine(destRecPos.x, destRecPos.y, otherEnemyRects[0].x, otherEnemyRects[0].y, RED);
        //    DrawText(std::to_string(Vector2Distance(destRecPos, Vector2{otherEnemyRects[0].x, otherEnemyRects[0].y})).c_str(), destRecPos.x, destRecPos.y - 10, 12, BLACK);
            slimeEnemyMovement.testingDrawDebug();
         }
         
    };
    class shootingEnemy : public basicEnemy{
        public:
        projectile_NS::projectileManager enemyProjectile;
        shootingEnemy(Vector2 aPos, std::string path, std::vector<std::vector<int>> aCollisionIDs): basicEnemy(aPos, path, aCollisionIDs) {
         }
         void shootLogic(){
            if(enemyProjectile.projectiles.size() < 1){
                enemyProjectile.addXProjectile(destRecPos, 6.00f, 6.00f, 1);
            }
             for(int i = 0; i < enemyProjectile.projectiles.size(); i++){
                enemyProjectile.projectiles[i].thePlayer = thePlayer;
            }
            enemyProjectile.update();
        }
        void deload(){
            for(int i = 0; i < enemyProjectile.projectiles.size(); i++){
                UnloadTexture(enemyProjectile.projectiles[i].projectileTexture);
            }
        }
    };
    class enemyManager{
        public:
        std::vector<basicEnemy> enemies;
        std::vector<std::unique_ptr<basicEnemy>> smartPtrEnemies; // (Example) smartPtrEnemies.push_back(std::make_unique<slimeEnemy>(Vector2{100,100}, "blueSlime.png"));

        enemyManager(){
            std::clog << "In enemyManager constructor" << std::endl;
            
        }
        void spawnEnemy(Vector2 spawnPointPos){
            enemies.push_back(basicEnemy(spawnPointPos));
        }
        void spawnSlimeEnemy(Vector2 spawnPointPos, std::string path, std::vector<std::vector<int>> aCollisionIDs){
           smartPtrEnemies.push_back(std::make_unique<slimeEnemy>(spawnPointPos, "blueSlime.png", aCollisionIDs));
        }
        void draw(){
            for(int i = 0; i < enemies.size(); i++){
                if(enemies[i].health == 199990){
                    killEnemy(i);
                }
                enemies[i].draw();
            }
        }
        void sDraw(){
            for(int i = 0; i < enemies.size(); i++){
                if(enemies[i].health == 199990){
                    killEnemy(i);
                }
                enemies[i].draw();
            }
            for(int j = 0; j < smartPtrEnemies.size(); j++){
                if(smartPtrEnemies[j]->health == 199990){
                    killEnemySPtr(j);
                }
                smartPtrEnemies[j]->draw();
                
            }
        }
        void deLoadTextures(){
            for(int i = 0; i < enemies.size(); i++){
                UnloadTexture(enemies[i].enemyTexture);
            }
        }
        void deLoadProjectiles(){
            for (auto& enemy : smartPtrEnemies){ // For each enemy in the vector
                     enemy->deload();
            } 
        }

        void update(){
            std::vector<Rectangle> enemiesRects;
            for(int i = enemies.size() - 1; i >= 0; i--){ // since killEnemy() resizes vector
                enemies[i].update();
                enemiesRects.push_back(enemies[i].destRec);
                if(enemies[i].health <= 0){
                    killEnemy(i); 
                    --i; // since killEnemy resizes vector
                }
            } 
            /*
            for(int j = 0; j < smartPtrEnemies.size(); j++){
                smartPtrEnemies[j]->update();
                enemiesRects->push_back(smartPtrEnemies[j]->destRec);
                if(smartPtrEnemies[j]->health <= 0){
                    killEnemy(j);
                }
            }
            for(int k = 0; k < enemies.size(); k++){
                enemies[k].otherEnemyRects = enemiesRects;
            }
            for(int l = 0; l < smartPtrEnemies.size(); l++){
                smartPtrEnemies[l]->otherEnemyRects = enemiesRects;
            }
            */
        }
        void sUpdate(){
            std::vector<Rectangle> enemiesRects;
            for(int i = enemies.size() - 1; i >= 0; i--){ // since killEnemy() resizes vector 
                enemies[i].update();
                enemiesRects.push_back(Rectangle{enemies[i].destRecPos.x, enemies[i].destRecPos.y, float(enemies[i].dWidth), float(enemies[i].dHeight)}); 
                if(enemies[i].health <= 0){
                    killEnemy(i); 
                    --i; // since killEnemy resizes vector
                }
            } 
            for(int j = smartPtrEnemies.size() - 1 ; j >= 0; j--){
                smartPtrEnemies[j]->update();
                enemiesRects.push_back(Rectangle{smartPtrEnemies[j]->destRecPos.x, smartPtrEnemies[j]->destRecPos.y, float(smartPtrEnemies[j]->dWidth), float(smartPtrEnemies[j]->dHeight)});
                if(smartPtrEnemies[j]->health <= 0){
                    killEnemySPtr(j);
                    --j; // since killEnemy resizes vector
                }
            }
         //   std::clog << "enemiesRects.size() = " << enemiesRects.size() << std::endl; 
            for(int k = enemies.size() - 1;  k >= 0; k--){
                std::vector<Rectangle> tempRects = enemiesRects;
                tempRects.erase(tempRects.begin() + k);   // Found error; logic error is somewhere here, tempRects has the same value as the currentEnemies position
                enemies[k].otherEnemyRects = tempRects;
            }
            //testing output 
          //  for(int p = 0; p < enemies.size(); p++){ 
             //   std::clog << "enemies Rect" << p << " = ";
             //   std::clog << enemiesRects[p].x << " " << enemiesRects[p].y << std::endl;
          //  }
            for(int l = smartPtrEnemies.size() - 1;  l >= 0; l--){
                std::vector<Rectangle> tempRects = enemiesRects;
                for(int t = tempRects.size() - 1; t >= 0; t--){
                if(tempRects[t].x == smartPtrEnemies[l]->destRecPos.x && tempRects[t].y == smartPtrEnemies[l]->destRecPos.y){
                 //   std::clog << "erasing values of tempRects = " <<tempRects[t].x << tempRects[t].y  << std::endl;
                    tempRects.erase(tempRects.begin() + t);
                    }
                }
                smartPtrEnemies[l]->otherEnemyRects = tempRects;
                for(int m = 0; m < tempRects.size(); m++){
               // std::clog << "tempRects Rect" << l << " = "; 
              //  std::clog << tempRects[m].x << " " << tempRects[m].y << std::endl;
                }
               // std::clog << "smarPtrEnemies Rect" << l << " = ";
               // std::clog << smartPtrEnemies[l]->destRecPos.x << " " << smartPtrEnemies[l]->destRecPos.y << std::endl;
              //  std::clog << "endl" << std::endl;
            }
        }
        void killEnemy(int index){
            UnloadTexture(enemies[index].enemyTexture);
            enemies.erase(enemies.begin() + index);
        }
        void killEnemySPtr(int index){
            UnloadTexture(smartPtrEnemies[index]->enemyTexture);
            smartPtrEnemies.erase(smartPtrEnemies.begin() + index);
        }
        void killEnemy(Vector2 enemyPos){
            for(int i = 0; i < enemies.size(); i++){
                if(enemies[i].destRecPos.x == enemyPos.x && enemies[i].destRecPos.y == enemyPos.y){
                    UnloadTexture(enemies[i].enemyTexture);
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    };
};

#endif