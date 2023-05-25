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

        // void stateManager();    
    };
  void player::draw(){
   DrawRectangleRec(playerRect, BLUE);  
  } 
};







#endif