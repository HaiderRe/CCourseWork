#ifndef player_objects_h
#define player_objects_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
namespace player_objects{
    class player{
        public:
        float xCord;
        float yCord;
        int width = 24; // Rect
        int height = 32; // Rect
        Vector2 destRecPos = {0.0f,0.0f};
        std::string currentAnim;
        Texture2D playerSprite;
        Vector2 sourceRecPos; 
        Rectangle playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        int health; 
        void draw();
        void checkFrame(); // Checks that need to be checked every frame, Plan to make this the "caller method" that calls other methods, rather than one BIG method
        void death();
        void update();
        void movement();

        // void stateManager();    
    };
    void player::movement(){
      if(IsKeyDown(KEY_RIGHT) ) {
        destRecPos.x += 2.00f;
        }
        else if(IsKeyDown(KEY_LEFT)){
            
        destRecPos.x += -2.00f;
        }
        if(IsKeyDown(KEY_DOWN)){
      
        destRecPos.y += 2.00f;
        }
        else if(IsKeyDown(KEY_UP)){
        destRecPos.y += -2.00f;
        }
        playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
    }
  void player::update(){
    movement();
  //  draw();
  }
  void player::draw(){
   DrawRectangleRec(playerRect, BLUE);  
  } 
};







#endif