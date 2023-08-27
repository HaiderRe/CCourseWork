#ifndef frameUtility_h
#define frameUtility_h
#include <iostream> 
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
namespace frameUtility_NS{
    class frameUtility{
        public: 
        int stayFrame = -1;
        int framesCounter = 0;
        int currentFrame = 0;
        Rectangle frameRec = {0.0f, 0.0f, 144, 144};
        Rectangle destRec = {0.0f, 0.0f, 32, 32};
        Vector2 testingVector = {0.00f, 0.00f};
        Texture2D texture;
        int maxFrames = 4;
        int framesPerSecond = 6;
        int frameWidth = 144; // For BlueSlime texture and others made by the same person
        int frameHeight = 144;
        int destWidth = 64; // Normally the same as destHeight
        int destHeight = 64;
        float rotation = 0.0f;
        Color color = WHITE;
        int direction = 0; // Used to determine which way the enemy is facing (0 = up, 1 = left, 2 = right, 3 = down) (if none 0 is used)
        frameUtility(Texture2D aTexture, int aFramesPerSecond, int aFrameWidth, int aFrameHeight, int aDestWidth, int aDestHeight, int aDirection){
            texture = aTexture;
            framesPerSecond = aFramesPerSecond;
            frameWidth = aFrameWidth;
            frameHeight = aFrameHeight;
            destWidth = aDestWidth;
            destHeight = aDestHeight;
            maxFrames = texture.width / frameWidth;
            direction = aDirection;
            frameRec = {0.0f, 0.0f, float(frameWidth), float(frameHeight)};
        }
        frameUtility(Texture2D aTexture){
            texture = aTexture;
        }
        frameUtility(){
            std::clog << "In frameUtility constructor" << std::endl;
        }
        void draw(){
            framesCounter++;
            frameRec.y = frameHeight * direction;
            if (framesCounter >= (60/framesPerSecond))
            {
                framesCounter = 0;
                currentFrame++;
                if (currentFrame > maxFrames) {
                    currentFrame = 0;
                }
                frameRec.x = frameWidth * currentFrame;
            }
            Vector2 origin = {frameRec.width * 0.5f, frameRec.height * 0.5f};
            if(frameRec.width == 144){
             //  std::clog << "all values of dest rec are  " << destRec.x << " " << destRec.y << " " << destRec.width << " " << destRec.height << std::endl; 
           //   DrawCircle(destRec.x, destRec.y, 5, GREEN); //  TRUE VALUES
                destRec.x = destRec.x + (origin.x) - (destWidth/4); // No clue why we need special code for 144pixel textures but we do
                destRec.y = destRec.y + (origin.y) - (destHeight/4); // Additionally both statements offset make the texture the midpoint of the
                                                                      // World position + half the width + half the height of the texture
               
            }
            else if(frameWidth == 100){
                std::clog << "explosion dest rec = " << destRec.x << " " << destRec.y << " " << destRec.width << " " << destRec.height << std::endl;         
                destRec.x = destRec.x;
                destRec.y = destRec.y;    
                origin = {0.00f, 0.00f};
            }
               else{ 
              //  DrawRectangle(destRec.x, destRec.y, destRec.width, destRec.height, BLUE);
                destRec.x = destRec.x + origin.x; // Top left corner of the texture is the destrec position
                destRec.y = destRec.y + origin.y;
               }
            if(stayFrame > -1){
                frameRec.x = frameWidth * stayFrame;
            }
            DrawTexturePro(texture, frameRec, destRec, origin, rotation, color);
            
        }
        void frameUtilityUpdateValues(int destRecx, int destRecy, int destWidth1, int destHeight1){
            destRec.x = float(destRecx);
            destRec.y = float(destRecy);
            destRec = {destRec.x, destRec.y, float(destWidth1), float(destHeight1)};
        }
        void frameUtilityUpdateValues(Rectangle aDestRec){
            destRec = aDestRec;
            
        }
        void frameUtilityDestroy(){
            UnloadTexture(texture);
        }
        void drawDebug(){
            return;
            
        }
    };
};
#endif