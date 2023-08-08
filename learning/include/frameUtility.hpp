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
        int framesCounter = 0;
        int currentFrame = 0;
        Rectangle frameRec = {0.0f, 0.0f, 144, 144};
        Rectangle destRec = {0.0f, 0.0f, 32, 32};
        Texture2D texture;
        int maxFrames = 4;
        int framesPerSecond = 6;
        int frameWidth = 144; // For BlueSlime texture and others made by the same person
        int frameHeight = 144;
        int destWidth = 64; // Normally the same as destHeight
        int destHeight = 64;
        float rotation = 0.0f;
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
            if(frameWidth == 144){
               std::clog << "all values of dest rec are  " << destRec.x << " " << destRec.y << " " << destRec.width << " " << destRec.height << std::endl; 
            }
            DrawTexturePro(texture, frameRec, destRec, {destRec.x/2, destRec.y/2}, rotation, WHITE);
        
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
    };
};
#endif