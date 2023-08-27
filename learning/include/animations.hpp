#ifndef animation_h
#define animations_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "game_renderer.hpp"
#include <vector>
namespace animations_h {
    class animationManager {
    public:
        std::string path; 
        int frames = 0;
        int currentFrame = 0;
        int frameSpeed = 6;
        bool isInfinte = false;
        bool isDone = false;
        float width;
        float rotation = 0.0f;
        int oldDirection = 0;
        float sWidth = 16;  // Update this In a method
        float sHeight = 16; // Update this in a method
        int amount_of_frames = 4;
        Vector2 position = {0.0f, 0.0f};
        float height;
        std::vector<std::string> paths;
        bool hasVector = false;
        Rectangle frameRec = {0.0f, 0.0f, (float)width, (float)height};
        Color playerColor1 = WHITE;
        Texture2D texture1;
        std::vector<Texture2D> texturesVector;
        animationManager(std::string iPath,  int iWidth, int iHeight, int iAmount_of_times){
            texture1 = LoadTexture(("Assets/" + iPath + ".png").c_str());
            path = iPath;
            width = iWidth;
            height = iHeight;
            amount_of_frames = iAmount_of_times;
            frameRec = {0.0f, 0.0f, (float)width/iAmount_of_times, (float)height};
        }
        animationManager(std::string iPath){
            texture1 = LoadTexture(("Assets/" + iPath + ".png").c_str());
            std::cout << "the path of the texutre is " << "Assets/" + iPath + ".png" << std::endl;
            path = iPath;
            width = (float) texture1.width;
            height = (float) texture1.height;
            std::cout << "called without wdith height and amount of frames" << std::endl; 
        }
        animationManager(std::string iPath, std::vector<std::string> iPaths){ 
            for(int i = 0; i < iPaths.size(); i++){
                //std::cout << "the path of the texutre is " << "Assets/" + iPaths[i] + ".png" << std::endl;
                texturesVector.push_back(LoadTexture(("Assets/" + iPaths[i] + ".png").c_str()));
            }
            path = iPaths[0];
            hasVector = true;
            paths = iPaths;
            frameRec = {0.0f, 0.0f, (float)width/amount_of_frames, (float)height};
        }
        void setColor(Color aColor){
            playerColor1 = aColor;
        }
        void draw(float x, float y){
            // Test draw the whole texture  
         //   DrawTexture(texture1, 0.00f, 0.00f, WHITE);
         frames++;
           if (frames >= (60/frameSpeed)){
              frames = 0;
              currentFrame++;
              if (currentFrame >= amount_of_frames) currentFrame = 0;
              frameRec.x = currentFrame * sWidth;
             }
        
         Rectangle destRec = { position.x, position.y, sWidth, sHeight};
         Vector2 origin = { width/2, height/2 };
         DrawTexturePro(texture1, frameRec, destRec, origin, rotation, playerColor1);
        }
        void deload(){
            UnloadTexture(texture1);
            for(int i = 0; i < texturesVector.size(); i++){
                UnloadTexture(texturesVector[i]);
            }
        }
        void draw(float x, float y, int direction){
            if(hasVector){
                drawV(x, y, direction);
                return; 
            } 
           // DrawTexture(texture1, 0.00f, 0.00f, WHITE);
         frames++;
         if(direction != oldDirection){ 
          //    currentFrame = 0;
              oldDirection = direction;
              frameRec.y = (float)direction*(float)sHeight;
            }
           if (frames >= (60/frameSpeed)){
              frames = 0;
              currentFrame++;
             if (currentFrame >= 4){
                currentFrame = 0;
             //   std::cout << "is done  =" << isDone << std::endl;
                if(isInfinte == false){
                    isDone = true;
                }
              }
              frameRec.x = (float)currentFrame*(float)sWidth;
             }
          // std::cout << "current frame is " << currentFrame << std::endl;
         //    std::cout << "frames is " << frames << std::endl;
         //    std::cout << "frame speed is " << frameSpeed << std::endl;
         //    std::cout << "60/framespeed is " << 60/frameSpeed << std::endl;
         Rectangle destRec = { position.x, position.y, sWidth, sHeight};
         Rectangle frameRec1 = {frameRec.x, frameRec.y, 64, 64}; 
         Vector2 origin = {  frameRec1.width/2, frameRec1.height/2};
      //   DrawTexture(texture1, 0.00f, 0.00f, WHITE);
         DrawTexturePro(texture1, frameRec1, destRec, origin, 0.00f, playerColor1);
     //    std::cout << "the frame rec is " << frameRec1.x << " " << frameRec1.y << " " << frameRec1.width << " " << frameRec1.height << std::endl;
     //    std::cout << "the dest rec is " << destRec.x << " " << destRec.y << " " << destRec.width << " " << destRec.height << std::endl;
      //   std::cout << "the origin is " << origin.x << " " << origin.y << std::endl;
        }
        // make a draw function that takes an array of paths an overlays them for the animation 
        void drawV(float x, float y, int direction){
            frames++;
            if(direction != oldDirection){ 
          //    currentFrame = 0;
              oldDirection = direction;
              frameRec.y = (float)direction*(float)sHeight;
            }
           if (frames >= (60/frameSpeed)){
              frames = 0;
              currentFrame++;
              if (currentFrame >= 4){
                currentFrame = 0;
              //   std::cout << "is done  =" << isDone << std::endl;
              //  std::cout << "is infinite  =" << isInfinte << std::endl;   
                if(isInfinte == false){
                    isDone = true;
                }
              }
              frameRec.x = (float)currentFrame*(float)sWidth;
             }
         Rectangle destRec = { position.x + 32 , position.y  + 32, sWidth, sHeight};
         Rectangle frameRec1 = {frameRec.x, frameRec.y, 64, 64}; 
         Vector2 origin = {  frameRec1.width/2, frameRec1.height/2};
         for(int i = 0; i < paths.size(); i++){
             DrawTexturePro(texturesVector[i], frameRec1, destRec, origin, rotation, playerColor1);
         }
        }
        void set_position(float x, float y){
            position.x = x;
            position.y = y;
        }
        void set_scale(float x, float y){
            sWidth = x;
            sHeight = y;
        }
        void set_frame_speed(int iFrameSpeed){
            frameSpeed = iFrameSpeed;
        }
        void update(float x, float y){
            set_position(x, y);
        }
        void destroy(){
            if(!hasVector){
            UnloadTexture(texture1); // Alternative to de-constructor
            }
            else{
                for(int i = 0; i < paths.size(); i++){
                    UnloadTexture(texturesVector[i]);
                }
            }
        }
       //  ~animationManager(){
         //   UnloadTexture(texture1); // create de-constructor
          //  std::cout << "animtion mangager de-constructor called for: " << path << std::endl; 
        //}

    };
};
#endif