
#ifndef slimeAttack_h
#define slimeAttack_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "frameUtility.hpp"
namespace slimeAttack_NS{
class Attack{
        public:
        std::string* currentState; // idle, attack, move, death, hurt(?),
        Vector2 playerPos = {0.00f, 0.00f};
        Vector2 speed = {6.00f, 6.00f}; //Modify as needed
        Vector2 *currentPos;
        frameUtility_NS::frameUtility attackFrameUtility;
        float coolDown = 2.00f;
        float coolDownTimer = 0.00f;
        int getReadyToAttack = 0;
        bool isAttacking = false;
        bool hitPlayer = false;
        bool intialPlayerPosSet = false;
        Vector2 intialPlayerPos = {0.00f, 0.00f};
        bool gettingReadyToAttack = false;
        Texture2D attackTexture;
        Attack(Vector2 *aPos){
         attackTexture = LoadTexture("Assets/enemy/blueSlime.png");
         attackFrameUtility = frameUtility_NS::frameUtility(attackTexture, 6, 144, 144, 64, 64, 0); 
         currentPos = aPos;
        }
        Attack(){}  
        void update(Vector2 aPlayerPos, Rectangle aDestRec, int aDirection){
            playerPos = aPlayerPos;
            attackFrameUtility.destRec = aDestRec;
            attackFrameUtility.direction = aDirection;
            isAttacking = false;
            shouldAttack();

        }
        void shouldAttack(){
            if(*currentState == "attack" && coolDownTimer > 0.00f){
                *currentState = "move";
            }
            if(*currentState == "attack" && coolDownTimer <= 0.00f){
                getReadyAttack();
             //   std::clog << "is getting ready and current state is attack and other shennagins" << std::endl;
                isAttacking = true;
                if(intialPlayerPosSet == false){
                    intialPlayerPosSet = true;
                    intialPlayerPos = {playerPos.x + 32, playerPos.y +32};
                    
                }
            }
              coolDownTimer -= GetFrameTime(); // Decrement CoolDown
            //    std::clog<< "cooldown" << coolDownTimer << std::endl;
        }
        void getReadyAttack(){
            getReadyToAttack += 1;
            gettingReadyToAttack = true;
            if(getReadyToAttack > 120){
                doAttack();
                gettingReadyToAttack = false;
            }
        }
        void doAttack(){
            Vector2 direction = Vector2Subtract(intialPlayerPos, *currentPos);
            float distanceToPlayer = Vector2Distance(*currentPos, intialPlayerPos);
            direction = Vector2Normalize(direction);
            direction = Vector2Scale(direction, speed.x);
            *currentPos = Vector2Add(*currentPos, direction);
            if(Vector2Length(direction) > distanceToPlayer){
                *currentPos = intialPlayerPos;
            }
            if(CheckCollisionRecs({currentPos->x - 32, currentPos->y - 32, 64, 64}, {playerPos.x + 24, playerPos.y + 16, 16, 32})){
                intialPlayerPosSet = false;
                isAttacking = false;
                hitPlayer = true;
                coolDownTimer = coolDown; //Set cooldown
                getReadyToAttack = 0;
                attackFrameUtility.rotation = 0.0f;
            }
            
            //check if we reached the intial player pos or if we overshot
            if(Vector2Equals(*currentPos, intialPlayerPos)){
                coolDownTimer = coolDown; //Set cooldown;
                attackFrameUtility.rotation = 0.0f;
                intialPlayerPosSet = false;
                isAttacking = false;
                getReadyToAttack = 0;
            }
        }
        void drawAttack(){
          //  DrawCircle(intialPlayerPos.x, intialPlayerPos.y, 5, RED);
          //  DrawCircle(currentPos->x, currentPos->y, 5, BLUE);
          //  DrawRectangleLines(playerPos.x + 24, playerPos.y + 16, 16, 32, RED);
            if(gettingReadyToAttack){
                Color aGrey = {189, 195, 199, 255};
                attackFrameUtility.color = aGrey;
                intialPlayerPos = {playerPos.x + 32, playerPos.y +32};
                attackFrameUtility.stayFrame = 1;
            }
            else{
                attackFrameUtility.color = WHITE;
                attackFrameUtility.stayFrame = -1;
            }
            if(isAttacking == true){
             //   attackFrameUtility.rotation = atan2(intialPlayerPos.y + 32 - currentPos->y, intialPlayerPos.x + 32 - currentPos->x) * 180 / PI;
                attackFrameUtility.draw();
            }
        }
    };
};
  #endif