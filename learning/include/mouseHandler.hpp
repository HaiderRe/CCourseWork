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
        Texture2D mouseTexture;
        mouseHandlerClass(){
            mousePos = {0,0};
            mouseTexture = LoadTexture("Assets/UI/crosshair005.png");
        }
        void update(){
            mousePos = GetMousePosition();
        }
        void draw(){
            int width = 5;
          //  DrawCircle(mousePos.x + width/2, mousePos.y + width/2, float(width), RED); 
         // std::cout << " FUIHduoif " << std::endl;
            DrawTexture(mouseTexture, mousePos.x, mousePos.y, WHITE);
        }
        Vector2 getMousePos(){
            return mousePos;
        }
        int isClicked(std::vector<Rectangle> buttons){ //returns the index of the button that is clicked 
            for(int i = 0; i < buttons.size(); i++){
                if(CheckCollisionPointRec(mousePos, buttons[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    return i;
                }
            }
            return -1;
        }

        };
    };
#endif