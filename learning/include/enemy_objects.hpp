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
        void playerCollision(); 
        virtual ~projectile() {
        
    }

    };
    void projectile::movement(){
        pos.x += speedX;
        pos.y += speedY;
        playerCollision();
    }
    void projectile::playerCollision(){
        extern player_objects::player nplayer;

    }
    class basicEnemy{
        public:
        int health; 
        int width = 32; // Rect
        int height = 32; // Rect
        float speedY;
        float speedX;
        Vector2 destRecPos = {0.0f,0.0f};
        Vector2 sourceRecPos;
        game_renderer_h_1::textureWrapper texture;
        void behaviour(); 
        void movement();
    };
    void basicEnemy::movement(){
     extern player_objects::player nplayer;
     
    }
};








#endif