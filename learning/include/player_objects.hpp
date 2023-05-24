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
        Vector2 pos = {0.0f,0.0f};
        int width = 24;
        int height = 32;
        void draw();
    };
  void player::draw(){
   DrawRectangle(pos.x, pos.y, width, height, BLUE);  
  } 
};







#endif