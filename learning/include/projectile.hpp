#ifndef projectile_h
#define projectile_h
#include <iostream> 
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "player_objects.hpp"
#include <vector>
namespace projectile_NS{
    class basicProjectile{
        public:
        float speedX = 1.00f;
        float speedY = 1.00f;
        Vector2 pos = {0,0};
        Rectangle frameRec = {0.0f, 0.0f, 64, 64};
        Rectangle destRec = {pos.x, pos.y, 24, 24};
        int currentFrame = 0;
        int framesCounter = 0;
        int framesSpeed = 8;
        bool isAlive = true;
        Texture2D projectileTexture;
        basicProjectile(Vector2 aPos, float IspeedX, float IspeedY){
            pos = aPos;
            speedX = IspeedX;
            speedY = IspeedY;
        } 
        basicProjectile(){
        }
    };
     class circleProjectile : public basicProjectile{
            public:
            player_objects::player *thePlayer;
            int intialXSpeed = 0;
            int intialYSpeed = 0;
            bool intialSpeedSet = false;
            circleProjectile(Vector2 aPos, float IspeedX, float IspeedY): basicProjectile(aPos, IspeedX, IspeedY) {
                projectileTexture = LoadTexture("assets/proj/fireball1/FireBall_2_64x64.png");
            }
            circleProjectile(){
            }
            void trackingMovement(){
                
            }
            void movement(){
                //Move towards player
                if(pos.x < 0 || pos.x > 4000 || pos.y < 0 || pos.y > 4000){
                    isAlive = false;
                    std::clog << "NOT ALIVE NOT ALIVE NOT ALIVE" << std::endl;
                    return;
                } 
                if(intialSpeedSet){
                 if(pos.x < thePlayer->destRecPos.x){
                    intialXSpeed = speedX;
                }
                if(pos.x > thePlayer->destRecPos.x){
                    intialXSpeed = -speedX;
                }
                if(pos.y < thePlayer->destRecPos.y){
                    intialYSpeed = speedY;
                }
                if(pos.y > thePlayer->destRecPos.y){
                    intialYSpeed = -speedY;
                }
                intialSpeedSet = true;
            }
            pos.x = pos.x + intialXSpeed;
            pos.y = pos.y + intialYSpeed;
            destRec = {pos.x, pos.y, 32, 32};
            }
            void update(){
                movement();
            }
            void draw(){;
                framesCounter++;
                int maxFrames = projectileTexture.width / 64;
                if (framesCounter >= (60/30))
                {
                    framesCounter = 0;
                    currentFrame++;
                    if (currentFrame > maxFrames) {
                        currentFrame = 0;
                    }
                    frameRec.x = 64 * currentFrame;
                }
                DrawTexturePro(projectileTexture, frameRec, destRec, {0,0}, 0, WHITE);
            }
        };
    class projectileManager{
        public: 
        std::vector<circleProjectile> projectiles;
        int amountOfAliveProjectiles = 0;
        void addXProjectile(Vector2 aPos, float IspeedX, float IspeedY, int amountOfProjectiles){
            int amountOfAliveProjectiles1 = 0;
            for(int i = 0; i < projectiles.size(); i++){
                if(!projectiles[i].isAlive){
                    amountOfAliveProjectiles1++;
                }
            }
            if(amountOfAliveProjectiles1 < amountOfProjectiles){
                for(int i = 0; i < amountOfProjectiles - amountOfAliveProjectiles1; i++){
                    projectiles.push_back(circleProjectile(aPos, IspeedX, IspeedY));

                }
                amountOfAliveProjectiles = amountOfAliveProjectiles1 - amountOfProjectiles;
            }
            projectiles.push_back(circleProjectile(aPos, IspeedX, IspeedY));
        }
        int getAmountOfAliveProj(){
            int xamountOfAliveProjectiles = 0;
                for(int i = 0; i < projectiles.size(); i++){
                    if(!projectiles[i].isAlive){
                        xamountOfAliveProjectiles++;
                    }
                }
                return xamountOfAliveProjectiles;
        }
        void update(){
            for(int i = 0; i < projectiles.size(); i++){
                projectiles[i].movement();
                if(projectiles[i].isAlive == false){
                    amountOfAliveProjectiles--; 
                    UnloadTexture(projectiles[i].projectileTexture);
                    projectiles.erase(projectiles.begin() + i);
                }
            }
        }
       void draw(){
        for(int i = 0; i < projectiles.size(); i++){
            projectiles[i].draw();
        }
       }
       void deLoadTextures(){
           for(int i = 0; i < projectiles.size(); i++){
               UnloadTexture(projectiles[i].projectileTexture);
           }
       }
    };
};

#endif