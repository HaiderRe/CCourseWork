#ifndef enemy_objects_h
#define enemy_objects_h
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
namespace enemy_objects_h_1{
    class basicEnemy{
        public:
        int health = 1; 
        int width = 32; // Rect
        int height = 32; // Rect
        float speedY;
        float speedX;
        Vector2 destRecPos = {0.0f,0.0f};
        Vector2 sourceRecPos;
        std::vector<projectile*> projectiles;
        bool hasProjectile = false;
        Rectangle enemyRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        game_renderer_h_1::textureWrapper texture;
        void movement();
        void draw();
        void death();
       // void playerCollision();
        void healthCheck();
        void frameCheck();
        void createProjectile();
        void projectileCollision();
        void createProjectilebehavior();
    };
    class projectile{ //need to implement a lot more here, code for deleteing projectiles  + more 
    //  Use Polymorphism 
        public: 
        float speedX; 
        float speedY;
        Vector2 pos; 
        basicEnemy* owner;
        Rectangle projectileRect = {pos.x, pos.y, float(width), float(height)};
        game_renderer_h_1::game_renderer* gameRenderP;
        projectile(Vector2 aPos, float IspeedX, float IspeedY, game_renderer_h_1::game_renderer* tGameRender){
            pos = aPos;
            speedX = IspeedX;
            speedY = IspeedY;
            gameRenderP = tGameRender;
            gameRenderP->projectilesEnemy.push_back(this);
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
            // check if the object is in the vector, if it is, delete it
           if(std::find(gameRenderP->projectilesEnemy.begin(), gameRenderP->projectilesEnemy.end(), this) != gameRenderP->projectilesEnemy.end()
            ){
                gameRenderP->projectilesEnemy.erase(std::remove(gameRenderP->projectilesEnemy.begin(), gameRenderP->projectilesEnemy.end(), this), gameRenderP->projectilesEnemy.end()); // As a pointer, also as long as the projectile is in the vector, it will be deleted
                delete this;
            }           
        }
        else if(pos.x > 4000 || pos.x < -400 || pos.y > 3000 || pos.y < -3000){
            // check if the object is in the vector, if it is, delete it
            if(std::find(gameRenderP->projectilesEnemy.begin(), gameRenderP->projectilesEnemy.end(), this) != gameRenderP->projectilesEnemy.end()
            ){
                gameRenderP->projectilesEnemy.erase(std::remove(gameRenderP->projectilesEnemy.begin(), gameRenderP->projectilesEnemy.end(), this), gameRenderP->projectilesEnemy.end()); // As a pointer, also as long as the projectile is in the vector, it will be deleted
                delete this;
            }
            
        }

    }
    
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
        createProjectilebehavior();
        if(hasProjectile){
            projectileCollision();
        }
    }
    void basicEnemy::death(){
        delete this;
    }
    void basicEnemy::healthCheck(){
        if(health <= 0){
            death();
        }
    }
    void basicEnemy::createProjectilebehavior(){
        if(hasProjectile){
            for(int i = 0; i < projectiles.size(); i++){
                projectiles[i]->behaviour(); //Arrow as a pointer
            }
        }
        else{
            createProjectile();
        }
    }
    void basicEnemy::createProjectile(){
        extern player_objects::player nplayer;
        extern game_renderer_h_1::game_renderer gameRenderer;
        Vector2 Tpos = {enemyRect.x, enemyRect.y};
        float TspeedX = (nplayer.destRecPos.x - enemyRect.x)/100;
        float TspeedY = (nplayer.destRecPos.y - enemyRect.y)/100;
        projectiles.push_back(new projectile(Tpos, TspeedX, TspeedY, &gameRenderer));
        hasProjectile = true;
    }
    void basicEnemy::projectileCollision(){

    }
};








#endif