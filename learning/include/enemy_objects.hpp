#ifndef enemy_objects_h
#define enemy_objects_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "game_renderer.hpp"
#include "player_objects.hpp"
namespace enemy_objects_h_1{
    class projectile{ //need to implement a lot more here, code for deleteing projectiles  + more 
    // Polymorphism 
        public: 
        float speedX; 
        float speedY;
        Vector2 pos;
        Rectangle projectileRect = {pos.x, pos.y, float(width), float(height)};
        game_renderer_h_1::game_renderer gameRenderP;
        projectile(Vector2 aPos, float IspeedX, float IspeedY, game_renderer_h_1::game_renderer tGameRender){
            pos = aPos;
            speedX = IspeedX;
            speedY = IspeedY;
            gameRenderP = tGameRender;
            gameRenderP.projectilesEnemy.push_back(this);
        }
        int width = 24;
        int height = 24;
        void movement();
        void projectileCollision(); 
        void draw();
        void behaviour();
        virtual ~projectile() {
        
    }

    };
    void projectile::draw(){
        DrawRectangleRec(projectileRect, RED);
    }
    void projectile::behaviour(){
        movement();
        draw();
        projectileCollision();

    }
    void projectile::movement(){
        pos.x += speedX;
        pos.y += speedY;
    }
    void projectile::projectileCollision(){
        extern player_objects::player nplayer;
        if(CheckCollisionRecs(nplayer.playerRect, projectileRect)){
            nplayer.health += -1;
            gameRenderP.projectilesEnemy.erase(std::remove(gameRenderP.projectilesEnemy.begin(), gameRenderP.projectilesEnemy.end(), this), gameRenderP.projectilesEnemy.end());
            delete this;
        }

    }
    class basicEnemy{
        public:
        int health = 1; 
        int width = 32; // Rect
        int height = 32; // Rect
        float speedY;
        float speedX;
        Vector2 destRecPos = {0.0f,0.0f};
        Vector2 sourceRecPos;
        Rectangle enemyRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        game_renderer_h_1::textureWrapper texture;
        void movement();
        void draw();
        void death();
        void playerCollision();

        void healthCheck();
        void frameCheck();
    };
    void basicEnemy::movement(){
     extern player_objects::player nplayer;
     if(CheckCollisionCircleRec(nplayer.destRecPos, nplayer.width/2, enemyRect)){
         nplayer.health += -1;
     }
        if(nplayer.destRecPos.x > enemyRect.x){
            enemyRect.x += 1;
        }
        else if(nplayer.destRecPos.x < enemyRect.x){
            enemyRect.x += -1;
        }
        if (nplayer.destRecPos.y > enemyRect.y){
            enemyRect.y += 1;
        }
        else if(nplayer.destRecPos.y < enemyRect.y){
            enemyRect.y += -1;
        }
    }
    void basicEnemy::draw(){
        DrawRectangleRec(enemyRect, RED);
    }
    void basicEnemy::frameCheck(){
        healthCheck();
        movement();
        draw();
    }
    void basicEnemy::death(){
        delete this;
    }
    void basicEnemy::healthCheck(){
        if(health <= 0){
            death();
        }
    }
};








#endif