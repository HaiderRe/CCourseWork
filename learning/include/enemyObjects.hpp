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
#include "game_renderer.hpp"
#include "player_objects.hpp"
namespace enemyObjects_NS{
    class basicEnemy{
        public:
        int health = 1;
        int dWidth = 32;
        int dHeight = 32;
        float speedY;
        float speedX;
        Vector2 destRecPos = {0.0f,0.0f};
        Rectangle frameRec = {0.0f, 0.0f, 32, 32};
        Rectangle destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
        Texture2D enemyTexture;
        basicEnemy(Vector2 spawnPointPos){
            destRecPos = spawnPointPos;
            destRec = {destRecPos.x, destRecPos.y, float(dWidth), float(dHeight)};
        }
        basicEnemy(){
            std::clog << "In basicEnemy constructor" << std::endl;
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
                DrawTextureRec(enemies[i].enemyTexture, enemies[i].frameRec, enemies[i].destRecPos, WHITE);
            }
        }
        void deLoadTextures(){
            for(int i = 0; i < enemies.size(); i++){
                UnloadTexture(enemies[i].enemyTexture);
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