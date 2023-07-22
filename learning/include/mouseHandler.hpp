#ifndef mouseHandler
#define mouseHandler
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
namespace mouseHandler{
    class mouseHandlerClass{
        public:
        Vector2 mousePos;   
        mouseHandlerClass(){
            mousePos = {0,0};
        }
        void update(){
            mousePos = GetMousePosition();
        }
        void draw(){
            DrawCircle(mousePos.x, mousePos.y, 5, RED);
        }
        Vector2 getMousePos(){
            return mousePos;
        }
    };
}
#endif