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
#include "sound.hpp"
namespace enemyObjects_NS{
    struct sound{
        std::string name;
        int index = -1;
    };
    class basicEnemy{
        public:
        int health = 3;
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
        sound damageSound;
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
        virtual void deloadSound(){
            return;
        }
        virtual void unloadTexture(){
            return;
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
    
    bool isColliding(int x, int y, std::vector<std::vector<int>> collisionIDsMap){
    if (x < 0 || x >= collisionIDsMap[0].size() || y < 0 || y >= collisionIDsMap.size()){
        return true; 
    }
    bool isCol = collisionIDsMap[y][x] != 0;
    return isCol;
    }
    };
    class slimeEnemy : public basicEnemy{
        public:
       // enemyAi_NS::simpleEnemyMovement slimeEnemyMovement;
       std::string stateMachineMemAcc = "idle";
       SoundManager& manager = SoundManager::getInstance();
       std::string* stateMachine; // idle, attack, move, death, hurt(?),
       enemyAi_NS::simpleEnemyMovement slimeEnemyMovement;
       slimeAttack_NS::Attack slimeAttack;
       int frameCountHealth = 60;
       float damageSoundTime = 0.0f;
         float damageSoundTimeMax = 0.5f;
             slimeEnemy(Vector2 aPos, std::string path, std::vector<std::vector<int>> aCollisionIDs): basicEnemy(aPos, path, aCollisionIDs) {
                slimeEnemyMovement = enemyAi_NS::simpleEnemyMovement(&destRecPos,  otherEnemyRects, aCollisionIDs);
                stateMachine = &stateMachineMemAcc;
                slimeEnemyMovement.currentState = stateMachine;
                slimeAttack = slimeAttack_NS::Attack(&destRecPos);
                slimeAttack.currentState = stateMachine;
                damageSound = {"damage", manager.loadSound("enemy/slimeHit.wav")};

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
                float damage = thePlayer->takeDamage(1.00f,destRecPos);
                if(damage > 0){
                    changeColorDamage();
                    takeDamage(damage);
                }
                slimeAttack.hitPlayer = false;
            }
         }
         void takeDamage(int damage){
            if(thePlayer->firstAttack == false){
                return;
            }
            health -= damage;
            if(damageSoundTime <= 0.00f){
            manager.playSound(damageSound.index);
            damageSoundTime = damageSoundTimeMax;
            }
            if(health <= 0){
                *stateMachine = "death";
            }
            knockBack();
         }
         void takeDamage(int damage, bool x){
            health -= damage;
            if(damageSoundTime <= 0.00f){
            manager.playSound(damageSound.index);
            damageSoundTime = damageSoundTimeMax;
            }
            if(health <= 0){
                *stateMachine = "death";
            }
            knockBack();
         }
         
         void changeColorDamage(){
                    enemyFrameUtility.color = RED;
                     slimeAttack.attackFrameUtility.color = RED;
                     frameCountHealth = 60;
         }

         void checkIsHitWeapon(){
            std::clog << "thePlayer->currentAnim = " << thePlayer->currentAnim << std::endl;
            if(thePlayer->currentAnim == "Player/base/Base_Attack"){
                std::clog << "TRUE" << std::endl;
                int direction = 0; // 0 = up , 1 = left, 2 = right, 3 = down
                direction = thePlayer->direction;
                Rectangle destRecPosPlayer = {thePlayer->destRecPos.x, thePlayer->destRecPos.y, 32, 32};
                 float offsetX = 0.0f;
                float offsetY = 0.0f;
                int width = 8;
                int height = 8;
                if(direction == 0){
                    offsetX += 24.0f;
                    offsetY += 00.0f;
                    height = 16;
                    width = 32;
                }
                if(direction == 1){
                    offsetY += 32.0f;
                    offsetX += 8.00;
                    width = 32;
                }
                if(direction == 2){
                    offsetX += 32.0f;
                    offsetY += 32.0f;
                    width = 32;
                }
                if(direction == 3){
                    offsetY += 32.0f;
                    offsetX += 24.0f;
                    width = 32;
                    height = 16;
                }
                Rectangle weaponHitBox = {destRecPosPlayer.x + offsetX, destRecPosPlayer.y + offsetY, width, height};
                Rectangle destRec1 = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
                if(CheckCollisionRecs(destRec1, weaponHitBox)){
                    takeDamage(thePlayer->weaponDamage);
                    enemyFrameUtility.color = RED;
                     slimeAttack.attackFrameUtility.color = RED;
                     frameCountHealth = 60;
                     std::clog << "TRUE HIT" << std::endl;
                }
            }
         }
         void checkIsHit(){
           checkIsHitFx();
           checkIsHitWeapon();

         }
         void checkIsHitFx(){
            int isHit = thePlayer->skillManagerObject.fxPlayerObject.hitBoxDecide(Rectangle{destRecPos.x,destRecPos.y, float(dWidth), float(dHeight)});
            std::clog << "is hit = " << isHit << std::endl;
            if(isHit){
                takeDamage(thePlayer->fxDamage, true);
                enemyFrameUtility.color = RED;
                std::clog << "TRUE HIT" << std::endl;
                slimeAttack.attackFrameUtility.color = RED;
                frameCountHealth = 60;
            }
         }
         void update() override{ // overriding update() from basicEnemy
            if(damageSoundTime > 0.00f){
                damageSoundTime -= GetFrameTime();
            }
            enemyFrameUtility.destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility.direction = direction;
            slimeEnemyMovement.update(otherEnemyRects, thePlayer->destRecPos);
             movement();
            slimeAttack.update(thePlayer->destRecPos, {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)}, direction);
            directionCalc();
            checkAttackHit();
            checkIsHit();
            if(frameCountHealth > 0){
                frameCountHealth--;
            }
            else{
                enemyFrameUtility.color = WHITE;
                slimeAttack.attackFrameUtility.color = WHITE;
            }
         }
         void unloadTexture() override{
             UnloadTexture(slimeAttack.attackTexture);
             UnloadTexture(enemyFrameUtility.texture);
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
            //slimeEnemyMovement.testingDrawDebug();
         }
    void knockBack(){

      Vector2 playerOffsetPos = {destRecPos.x , destRecPos.y }; 
      Vector2 enemyCenter = Vector2Add(thePlayer->destRecPos, Vector2{16 ,16}) ;
      Vector2 direction = {playerOffsetPos.x - enemyCenter.x, playerOffsetPos.y - enemyCenter.y};
      float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
      if (magnitude == 0){
        return; 
      }
    Vector2 normalizedDirection = {direction.x / magnitude, direction.y / magnitude};
    float knockbackDistance = 48.0f;
    Vector2 knockback = {normalizedDirection.x * knockbackDistance, normalizedDirection.y * knockbackDistance};
    Vector2 newPos = {destRecPos.x + knockback.x, destRecPos.y + knockback.y};
    int playerX = newPos.x / 16;
    int playerY = newPos.y / 16;
    float stepSize = 1.0f; 
    int maxAttempts = 16;  
    int attempts = 0;
    while (isColliding(playerX, playerY, thePlayer->collisionIDsMap) && attempts < maxAttempts) {
        newPos.x += normalizedDirection.x * stepSize;
        newPos.y += normalizedDirection.y * stepSize;
        playerX = newPos.x / 16;
        playerY = newPos.y / 16;
        attempts++;
    }
    destRecPos = newPos;
    }
    };
    class shootingEnemy : public basicEnemy{
        public:
        projectile_NS::projectileManager enemyProjectile;
        enemyAi_NS::simpleEnemyMovement shootingEnemyMovement;
         std::string stateMachineMemAcc = "idle";
         std::string* stateMachine = &stateMachineMemAcc; // idle, attack, move, death, hurt(?),
         enemyAi_NS::DirectApproachEnemy directApproachEnemy;
         frameUtility_NS::frameUtility projectileFrameUtility;
         frameUtility_NS::frameUtility explosionFrameUtility;
         Vector2 projectilePos = {0.0f, 0.0f};
         Vector2 intialPlayerPos = {0.0f, 0.0f};
         Vector2 projectileSpeed = {4.0f, 4.0f};
         float explosionTime = 6.0f;
         float currentExplosionTime = 0.0f;
         float projectileLife = 0.0f;
         float damageSoundTime = 0.0f;
         float damageSoundTimeMax = 0.5f;
         Vector2 explosionPos = {0.0f, 0.0f}; // Explosion handling next bye
         bool intialExplosionPosSet = false;
         bool isExploding = false;
         bool intialPlayerPosSet = false; 
         bool isAttacking = false;
         bool isAttacking1 = false;
         Vector2 directionPos = {0.00f, 0.00f};
       int frameCountHealth = 60;
        SoundManager& manager = SoundManager::getInstance();
       Texture2D expTexture = LoadTexture("Assets/proj/roundExpl/spritesheet.png");
        Texture2D projectileTexture = LoadTexture("Assets/proj/fastPixelFire/spritesheet.png");
        shootingEnemy(Vector2 aPos, std::string path, std::vector<std::vector<int>> aCollisionIDs): basicEnemy(aPos, path, aCollisionIDs) {
                shootingEnemyMovement = enemyAi_NS::simpleEnemyMovement(&destRecPos,  otherEnemyRects, aCollisionIDs, 64.00f, 72.00f);
                directApproachEnemy = enemyAi_NS::DirectApproachEnemy(&destRecPos,  64.00f, 1.50f,  aCollisionIDs); // distance, speed, collisionIDs
                UnloadTexture(projectileFrameUtility.texture);
                projectileFrameUtility = frameUtility_NS::frameUtility(projectileTexture, 60, 173, 197, 32, 32, 0);
                explosionFrameUtility = frameUtility_NS::frameUtility(expTexture, 60, 100, 100, 32, 32, 0);
                directApproachEnemy.isAttacking = &isAttacking;
                stateMachine = &stateMachineMemAcc;
                shootingEnemyMovement.currentState = stateMachine;
                dWidth = 64;
                dHeight = 64;
                UnloadTexture(enemyFrameUtility.texture);
                damageSound = {"damage", manager.loadSound("enemy/damage.wav")};
                if(path.size() > 0){
                enemyFrameUtility.texture = LoadTexture(("Assets/enemy/" + path).c_str());
                }
                else{
                    enemyFrameUtility.texture = LoadTexture("Assets/enemy/fireMan.png");
                }
                
         }

         void takeDamage(int damage){
            if(thePlayer->firstAttack == false){
                return;
            }
            health -= damage;
            knockBack();
            if(damageSoundTime <= 0.00f){
            manager.playSound(damageSound.index);
            damageSoundTime = damageSoundTimeMax;
            }
            if(health <= 0){
                *stateMachine = "death";
            }
         }
         void takeDamage(int damage, bool x){
            health -= damage;
            knockBack();
            if(damageSoundTime <= 0.00f){
            manager.playSound(damageSound.index);
            damageSoundTime = damageSoundTimeMax;
            }
            if(health <= 0){
                *stateMachine = "death";
            }
         }
void knockBack(){

      Vector2 playerOffsetPos = {destRecPos.x + 32, destRecPos.y + 32}; 
      Vector2 enemyCenter = Vector2Add(thePlayer->destRecPos, Vector2{16 ,16}) ;
      Vector2 direction = {playerOffsetPos.x - enemyCenter.x, playerOffsetPos.y - enemyCenter.y};
      float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
      if (magnitude == 0){
        return; 
      }
    Vector2 normalizedDirection = {direction.x / magnitude, direction.y / magnitude};
    float knockbackDistance = 48.0f;
    Vector2 knockback = {normalizedDirection.x * knockbackDistance, normalizedDirection.y * knockbackDistance};
    Vector2 newPos = {destRecPos.x + knockback.x, destRecPos.y + knockback.y};
    int playerX = newPos.x / 16;
    int playerY = newPos.y / 16;
    float stepSize = 1.0f; 
    int maxAttempts = 16;  
    int attempts = 0;
    while (isColliding(playerX, playerY, thePlayer->collisionIDsMap) && attempts < maxAttempts) {
        newPos.x += normalizedDirection.x * stepSize;
        newPos.y += normalizedDirection.y * stepSize;
        playerX = newPos.x / 16;
        playerY = newPos.y / 16;
        attempts++;
    }
    destRecPos = newPos;
    }
             void checkIsHitFx(){
            int isHit = thePlayer->skillManagerObject.fxPlayerObject.hitBoxDecide(Rectangle{destRecPos.x,destRecPos.y, 32, float(dHeight)});
            if(isHit){
                takeDamage(thePlayer->fxDamage, true);
                enemyFrameUtility.color = RED;
                frameCountHealth = 60;
            }
         }
          void checkIsHitWeapon(){
            if(thePlayer->currentAnim == "Player/base/Base_Attack"){
               int direction = 0; // 0 = up , 1 = left, 2 = right, 3 = down
                direction = thePlayer->direction;
                Rectangle destRecPosPlayer = {thePlayer->destRecPos.x, thePlayer->destRecPos.y, 32, 32};
                 float offsetX = 0.0f;
                float offsetY = 0.0f;
                int width = 8;
                int height = 8;
                if(direction == 0){
                    offsetX += 24.0f;
                    offsetY += 00.0f;
                    height = 16;
                    width = 32;
                }
                if(direction == 1){
                    offsetY += 32.0f;
                    offsetX += 8.00;
                    width = 32;
                }
                if(direction == 2){
                    offsetX += 32.0f;
                    offsetY += 32.0f;
                    width = 32;
                }
                if(direction == 3){
                    offsetY += 32.0f;
                    offsetX += 24.0f;
                    width = 32;
                    height = 16;
                }
                width = 16;
                 Rectangle weaponHitBox = {destRecPosPlayer.x + offsetX, destRecPosPlayer.y + offsetY, width, height};
                Rectangle destRec1 = {destRecPos.x, destRecPos.y, 32, float(dHeight)};

                if(CheckCollisionRecs(destRec1, weaponHitBox)){
                    takeDamage(thePlayer->weaponDamage);
                    enemyFrameUtility.color = RED;
                     frameCountHealth = 60;
                }
            }
         }
         void testingDrawDebugD(){
                return;
         }
          void directionCalc(){

            if(destRecPos.x < thePlayer->destRecPos.x + 64){
                direction = 2;
            }
            else{
                direction = 1;
            }
            if( destRecPos.y  < thePlayer->destRecPos.y - 16) // cjamge cjpde
            {
                direction = 0;
            }
            else if(destRecPos.y - 32 > thePlayer->destRecPos.y + 32){
                direction = 3;
            }
         }
         void movement () override{
           std::string x = directApproachEnemy.movement();
           if(x == "attack"){
               *stateMachine = "attack";
               isAttacking1 = true;
           }
           else{
               *stateMachine = "idle";
           }
         }
         void projectileMovement(){
            projectileLife = projectileLife + GetFrameTime();
            if(intialPlayerPosSet == false){
                directionPos = {0.00f, 0.00f};
                intialPlayerPos = {thePlayer->destRecPos.x + 32, thePlayer->destRecPos.y + 32};
                intialPlayerPosSet = true;
                projectilePos = destRecPos;
                isAttacking = true;
                isAttacking1 = true;
                isExploding = false;
            directionPos = Vector2Subtract(intialPlayerPos, projectilePos);
            float distanceToPlayer = Vector2Distance(projectilePos, intialPlayerPos);
            directionPos = Vector2Normalize(directionPos);
            directionPos = Vector2Scale(directionPos, projectileSpeed.x);
            }
            float distanceToPlayer = Vector2Distance(projectilePos, intialPlayerPos);
            projectilePos = Vector2Add(projectilePos, directionPos);
            if(Vector2Distance(projectilePos, intialPlayerPos) < 8.00f && false){
                 intialPlayerPosSet = false;
                isAttacking = false;
                isAttacking1 = false;
                projectileLife = 0.00f;
                isExploding = true;
                explosionFrameUtility.frameUtilityUpdateValues(projectilePos.x, projectilePos.y, 32, 32);
                explosionFrameUtility.destRec = {projectilePos.x, projectilePos.y, 32, 32};
                *stateMachine = "idle";
                directApproachEnemy.attackDone = true;
            }
            if(projectileLife > 7.00f){
                intialPlayerPosSet = false;
                isAttacking = false;
                isAttacking1 = false;
                projectileLife = 0.00f;
               isExploding = true;
                explosionFrameUtility.frameUtilityUpdateValues(projectilePos.x, projectilePos.y, 32, 32);
                explosionFrameUtility.destRec = {projectilePos.x, projectilePos.y, 32, 32};
                *stateMachine = "idle";
                directApproachEnemy.attackDone = true;
            }
            if(Vector2Length(directionPos) > distanceToPlayer && false){ //Testing 
               intialPlayerPosSet = false;
                isAttacking = false;
                isAttacking1 = false;
                projectileLife = 0.00f;
                isExploding = true;
                explosionFrameUtility.frameUtilityUpdateValues(projectilePos.x, projectilePos.y, 32, 32);
                explosionFrameUtility.destRec = {projectilePos.x, projectilePos.y, 32, 32};
                *stateMachine = "idle";
                directApproachEnemy.attackDone = true;
            }
            if(CheckCollisionRecs({projectilePos.x, projectilePos.y, 32, 32}, {thePlayer->destRecPos.x + 24, thePlayer->destRecPos.y + 16, 16, 32})){
                 intialPlayerPosSet = false;
                isAttacking = false;
                isAttacking1 = false;
                projectileLife = 0.00f; 
                isExploding = true;
                explosionFrameUtility.frameUtilityUpdateValues(projectilePos.x, projectilePos.y, 32, 32);
                explosionFrameUtility.destRec = {projectilePos.x, projectilePos.y, 32, 32};
               *stateMachine = "idle";
                directApproachEnemy.attackDone = true;
                float damage = thePlayer->takeDamage(1.00f,destRecPos);
                if(damage){
                    takeDamage(damage);
                    enemyFrameUtility.color = RED;
                     frameCountHealth = 60;
                }
            }
         }
         void projectileDraw(){
            Rectangle destRec = {projectilePos.x, projectilePos.y, 32, 32};
            Rectangle destRec1 = {projectilePos.x , projectilePos.y , 32, 32};
            projectileFrameUtility.frameUtilityUpdateValues(destRec.x, destRec.y, destRec.width, destRec.height);
            projectileFrameUtility.draw();
          //  DrawRectangleLines(destRec1.x, destRec1.y, destRec1.width, destRec1.height, RED);

         }
         void draw() override{
            if(*stateMachine == "attack" || isAttacking == true || isAttacking1 == true){
             projectileDraw();
            }
           
            enemyFrameUtility.draw();
            enemyFrameUtility.drawDebug();
            if(isExploding){
                explosionFrameUtility.draw();
                // DrawRectangleLines(explosionFrameUtility.destRec.x, explosionFrameUtility.destRec.y, explosionFrameUtility.destRec.width, explosionFrameUtility.destRec.height, RED);
            }
            testingDrawDebugD();
          //  DrawLine(destRecPos.x, destRecPos.y, otherEnemyRects[0].x, otherEnemyRects[0].y, RED);
        //    DrawText(std::to_string(Vector2Distance(destRecPos, Vector2{otherEnemyRects[0].x, otherEnemyRects[0].y})).c_str(), destRecPos.x, destRecPos.y - 10, 12, BLACK);
         }
         void explodeLife(){
            currentExplosionTime = currentExplosionTime + GetFrameTime();
            if(currentExplosionTime > explosionTime){
                isExploding = false;
                currentExplosionTime = 0.0f;
            }
         }
         void update() override{ // overriding update() from basicEnemy
         if(damageSoundTime > 0.00f){
             damageSoundTime += -GetFrameTime();
         }
            enemyFrameUtility.destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility.direction = direction;
            
            shootingEnemyMovement.update(otherEnemyRects, thePlayer->destRecPos);
            if(isAttacking == true || isAttacking1 == true || *stateMachine == "attack"){
                projectileMovement();
            }
            if(isExploding){
                explodeLife();
            }
            checkIsHitWeapon();
            checkIsHitFx();
            directApproachEnemy.update(thePlayer->destRecPos);
            directionCalc();
             movement();
            if(frameCountHealth > 0){
                frameCountHealth--;
            }
            else{
                enemyFrameUtility.color = WHITE;
            }
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
          //  for(int i = 0; i < enemyProjectile.projectiles.size(); i++){
         //       UnloadTexture(enemyProjectile.projectiles[i].projectileTexture);
        //    }
            
            UnloadTexture(projectileTexture);
        }
        void deloadSound() override{
            manager.unloadSound(damageSound.index);
        }
     void unloadTexture() override{
            UnloadTexture(projectileTexture);
             UnloadTexture(enemyFrameUtility.texture);
             UnloadTexture(projectileFrameUtility.texture);
         }
    };
    class enemyManager{
        public:
        std::vector<basicEnemy> enemies;
        std::vector<std::unique_ptr<basicEnemy>> smartPtrEnemies; // (Example) smartPtrEnemies.push_back(std::make_unique<slimeEnemy>(Vector2{100,100}, "blueSlime.png"));
        SoundManager& manager = SoundManager::getInstance();
        int enemiesKilled = 0;
        enemyManager(){
            std::clog << "In enemyManager constructor" << std::endl;
            
        }
        void reset(){
            for(int i = 0; i < smartPtrEnemies.size(); i++){
                smartPtrEnemies[i]->unloadTexture();
            }
            enemies.clear();
            smartPtrEnemies.clear();
            enemiesKilled = 0;
        }
        int howManyEnemies(){
            return enemies.size() + smartPtrEnemies.size();
        }
        void spawnEnemy(Vector2 spawnPointPos){
            enemies.push_back(basicEnemy(spawnPointPos));
        }
        void spawnSlimeEnemy(Vector2 spawnPointPos, std::string path, std::vector<std::vector<int>> aCollisionIDs){
           smartPtrEnemies.push_back(std::make_unique<slimeEnemy>(spawnPointPos, "blueSlime.png", aCollisionIDs));
        }
        void spawnShootingEnemy(Vector2 spawnPointPos, std::string path, std::vector<std::vector<int>> aCollisionIDs){
            smartPtrEnemies.push_back(std::make_unique<shootingEnemy>(spawnPointPos, path, aCollisionIDs));
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
            if(enemies.size() && smartPtrEnemies.size() == 0){
                return;
            }
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
            if(enemies.size() && smartPtrEnemies.size() == 0){
                return;
            }
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
                if(j >= smartPtrEnemies.size()){
                    break;
                }
                smartPtrEnemies[j]->update();
                enemiesRects.push_back(Rectangle{smartPtrEnemies[j]->destRecPos.x, smartPtrEnemies[j]->destRecPos.y, float(smartPtrEnemies[j]->dWidth), float(smartPtrEnemies[j]->dHeight)});
                if(smartPtrEnemies[j]->health <= 0){
                    killEnemySPtr(j);
                    --j; 
                }
            }
         //   std::clog << "enemiesRects.size() = " << enemiesRects.size() << std::endl; 
            for(int k = enemies.size() - 1;  k >= 0; k--){
                std::vector<Rectangle> tempRects = enemiesRects;
                tempRects.erase(tempRects.begin() + k);   // 
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
            manager.unloadSound(enemies[index].damageSound.index);
            enemies[index].deload();
            enemies.erase(enemies.begin() + index);
            enemiesKilled++;
        }
        void killEnemySPtr(int index){
             UnloadTexture(smartPtrEnemies[index]->enemyTexture);
             smartPtrEnemies[index]->deloadSound();
            smartPtrEnemies[index]->deload();
          //  smartPtrEnemies[index]->unloadTexture();
          //  UnloadTexture(smartPtrEnemies[index]->enemyFrameUtility.texture);
             
            smartPtrEnemies.erase(smartPtrEnemies.begin() + index);
            enemiesKilled++;
        }
        void killEnemy(Vector2 enemyPos){
            for(int i = 0; i < enemies.size(); i++){
                if(enemies[i].destRecPos.x == enemyPos.x && enemies[i].destRecPos.y == enemyPos.y){
                    enemies[i].deload();
                    UnloadTexture(enemies[i].enemyTexture);
                    enemies.erase(enemies.begin() + i);
                    enemiesKilled++;
                    break;
                }
            }
        }
    };
};

#endif