#ifndef player_objects_h
#define player_objects_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "animations.hpp"
#include <vector>
#include "json.hpp"
namespace player_objects{
  class playerAnimations{
    public: 
    std::vector<animations_h::animationManager> animations;
    std::string currentAnimation;
    int pKey = 0;
    void addAnimation(std::string path, int width, int height, int amount_of_frames){
      animations.push_back(animations_h::animationManager(path, width, height, amount_of_frames));
    }
    void addAnimation(std::string path, int width, int height){
    // Make the animation manager have the amount of frames equal to its width divided by the player's width.
    animations.push_back(animations_h::animationManager(path));
    animations_h::animationManager& anim = animations.back();
    anim.sWidth = width;
    anim.sHeight = height;
    anim.amount_of_frames = anim.sWidth / width;
}
void addAnimation(std::string path, int width, int height, std::vector<std::string> iPaths){
    // Make the animation manager have the amount of frames equal to its width divided by the player's width.
    animations.push_back(animations_h::animationManager(path, iPaths));
    animations_h::animationManager& anim = animations.back();
    anim.sWidth = width;
    anim.sHeight = height;
    anim.amount_of_frames = anim.sWidth / width;
}
    void currentAnimationManager(){
      for(int i = 0; i < animations.size(); i++){
        if(animations[i].path == currentAnimation){
          pKey = i;
          break;
        }
      }
    }
    void draw(float x, float y, int direction){
      animations[0].draw(x, y, direction);
    }
    void switchAnimation(std::string path){
      currentAnimation = path;
      currentAnimationManager();
    }
  };
    // Path of the animation expects no .png and no Assets/ just the name of the file
    class player{
        public:
        float xCord;
        float yCord;
        int width = 64; // Rect
        int height = 64; // Rect
        Vector2 destRecPos = {0.0f,0.0f};
        std::string currentAnim;
        int direction = 0; // 0 = up , 1 = left, 2 = right, 3 = down
        playerAnimations playerAnims;
        Texture2D playerSprite;
        Vector2 sourceRecPos; 
        Rectangle playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        int health; 
        void draw();
        void update();
        void movement();
        player(){
          std::vector<std::string> iPaths;
          iPaths.push_back("Assets/Player/base/Base_Idle");
          iPaths.push_back("Assets/Player/hair/Base_Idle_Hair_3");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Shoes_1");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Pants_1");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Gloves_1");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Chest_1");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Hat_1");
          iPaths.push_back("Assets/Player/armor/06_fateful/Base_Idle_Fateful_Chest_1A");
          playerAnims.addAnimation("Base_Attack", width, height, iPaths);
          playerAnims.addAnimation("Base_Idle", width, height);
          playerAnims.addAnimation("Base_Walk", width, height);
          playerAnims.addAnimation("Base_Dead", width, height);

       /*   playerAnims.addAnimation("player2", width, height);
          playerAnims.addAnimation("player3", width, height);
          playerAnims.addAnimation("player4", width, height);
          playerAnims.addAnimation("player5", width, height);
          playerAnims.addAnimation("player6", width, height);
          */
        }
        void set_animationManagerWidthAndHeight(int width, int height){
          playerAnims.animations[playerAnims.pKey].sWidth = width;
          playerAnims.animations[playerAnims.pKey].sHeight = height;
        }
        void switchAnimation(std::string path){
          playerAnims.switchAnimation(path);
          set_animationManagerWidthAndHeight(width, height);
        }
        // void stateManager();    
    };
    void player::movement(){
      if(IsKeyDown(KEY_RIGHT) ) {
        destRecPos.x += 2.00f;
        direction = 2;
        }
        else if(IsKeyDown(KEY_LEFT)){
            
        destRecPos.x += -2.00f;
        direction = 1;
        }
        if(IsKeyDown(KEY_DOWN)){
      
        destRecPos.y += 2.00f;
        direction = 3;
        }
        else if(IsKeyDown(KEY_UP)){
        destRecPos.y += -2.00f;
        direction = 0;
        }
        playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        // set poisition of the player in the animation manager using set_position
        playerAnims.currentAnimationManager();
        playerAnims.animations[playerAnims.pKey].set_position(destRecPos.x, destRecPos.y);
    }
  void player::update(){
    movement();
  //  draw();
  }
  void player::draw(){
    playerAnims.draw(destRecPos.x, destRecPos.y, direction);
  } 
  
};







#endif