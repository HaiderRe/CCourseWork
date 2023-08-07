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
        projectile_NS::projectileManager enemyProjectile;
        player_objects::player *thePlayer; // Add player else where
        frameUtility_NS::frameUtility enemyFrameUtility;
        basicEnemy(Vector2 spawnPointPos){
            destRecPos = spawnPointPos;
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility = frameUtility_NS::frameUtility(enemyTexture, 6, 144, 144, 64, 64, direction);
        }
        basicEnemy(){
            std::clog << "In basicEnemy constructor" << std::endl;
            enemyFrameUtility = frameUtility_NS::frameUtility(enemyTexture, 6, 144, 144, 64, 64, direction);
        }
        void shootLogic(){

            if(enemyProjectile.projectiles.size() < 1){
                enemyProjectile.addXProjectile(destRecPos, 3, 3, 1);
                enemyProjectile.projectiles[0].speedX = 2.00f;
                enemyProjectile.projectiles[0].speedY = 2.00f;
            }
             for(int i = 0; i < enemyProjectile.projectiles.size(); i++){
                enemyProjectile.projectiles[i].thePlayer = thePlayer;
            }
            enemyProjectile.update();
        }
        void shouldShoot();
        
        void movement(){
            //Move towards player
            if(destRecPos.x < 0 || destRecPos.x > 4000 || destRecPos.y < 0 || destRecPos.y > 4000){
                health = 0;
                return;
            }
            std::clog << "player position is " << thePlayer->destRecPos.x << " " << thePlayer->destRecPos.y << std::endl;
            if(destRecPos.x < thePlayer->destRecPos.x){
                destRecPos.x += speedX;
                direction = 2;
            }
            if(destRecPos.x > thePlayer->destRecPos.x){
                destRecPos.x -= speedX;
                direction = 1;
            }
            if(destRecPos.y < thePlayer->destRecPos.y){
                destRecPos.y += speedY;
                direction = 0;
            }
            if(destRecPos.y > thePlayer->destRecPos.y){
                destRecPos.y -= speedY;
                direction = 3;
            }
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
           
        }
        void draw(){
            enemyFrameUtility.draw();
            std::clog << "Drawing enemy " << std::endl;
            enemyProjectile.draw();
        }
        void update(){
            movement();
            enemyFrameUtility.destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
            enemyFrameUtility.direction = direction;
            shootLogic();
        }
    };
    class enemyManager{
        public:
        std::vector<basicEnemy> enemies;
        enemyManager(){
            std::clog << "In enemyManager constructor" << std::endl;
        }
        void spawnEnemy(Vector2 spawnPointPos){
            enemies.push_back(basicEnemy(spawnPointPos));
        }
        void draw(){
            for(int i = 0; i < enemies.size(); i++){
                if(enemies[i].health == 199990){
                    killEnemy(i);
                }
                enemies[i].draw();
            }
        }
        void deLoadTextures(){
            for(int i = 0; i < enemies.size(); i++){
                UnloadTexture(enemies[i].enemyTexture);
            }
        }
        void update(){
            for(int i = 0; i < enemies.size(); i++){
                enemies[i].update();
                if(enemies[i].health <= 0){
                    killEnemy(i);
                }
            }
            
        }
        void killEnemy(int index){
            UnloadTexture(enemies[index].enemyTexture);
            enemies.erase(enemies.begin() + index);
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