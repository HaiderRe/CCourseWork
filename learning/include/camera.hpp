#ifndef camera_h
#define camera_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include <vector>
#include "player_objects.hpp"
namespace camera_h {
    class camera_class {
    public:
        player_objects::player &player;
        Camera2D cam;
        camera_class(player_objects::player& player_input);
        void update();
        void debugger();
        void followPlayer();
    };

      camera_class::camera_class(player_objects::player& player_input) : player(player_input) {
        cam = {0};
        cam.zoom = 4.0f;
        cam.target = Vector2{ 0.0f, 0.0f };
        cam.offset = Vector2{ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
        cam.rotation = 0.0f;
        player = player_input;
    }
    void camera_class::update() {
        followPlayer();
        debugger();
    }
    void camera_class::followPlayer() {
    Vector2 targetPos = Vector2{player.destRecPos.x + (player.width /2), player.destRecPos.y + (player.height /2)};
    float linearInter = 0.1f;   // Factor of linear interpolation for camera smoothing, needs to be changed to a variable that can be changed in game as doesn't work well with different speeds of player
    cam.target.x = cam.target.x + (targetPos.x - cam.target.x) * linearInter;
    cam.target.y = cam.target.y + (targetPos.y - cam.target.y) * linearInter;
    }
    void camera_class::debugger(){
        if(IsKeyDown(KEY_F8)){
            cam.zoom += 0.1f;
        }
        if(IsKeyDown(KEY_F7)){
            cam.zoom -= 0.1f;
        }
        if(IsKeyDown(KEY_F6)){
            cam.rotation += 0.1f;
        }
        if(IsKeyDown(KEY_F5)){
            cam.rotation -= 0.1f;
        }
    }
};
#endif