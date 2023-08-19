
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
        frameUtility_NS::frameUtility attackFrameUtility;
        Attack(){
         Texture2D attackTexture = LoadTexture("Assets/enemy/blueSlime.png");
         attackFrameUtility = frameUtility_NS::frameUtility(attackTexture, 6, 144, 144, 64, 64, 0); 

        }
        void update(Vector2 aPlayerPos, Rectangle aDestRec, int aDirection){
            playerPos = aPlayerPos;
            attackFrameUtility.destRec = aDestRec;
            attackFrameUtility.direction = aDirection;
        }
    };
};
  #endif