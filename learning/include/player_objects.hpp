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
    std::string currentAnimation = "Base_Attack";
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
    if(anim.path == "Player/base/Base_Idle"){
      anim.isInfinte = true;
    }
    if(anim.path == "Player/base/Base_Walk"){
      anim.isInfinte = true;
    }
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
    std::string currentAnimationPath(){
      return animations[pKey].path;
    }
    void draw(float x, float y, int direction){
      animations[pKey].draw(x, y, direction);
      if(animations[pKey].isDone == true){
        animations[pKey].isDone = false;
        switchAnimation("Player/base/Base_Idle");
      }
    }
    void switchAnimation(std::string path){
      currentAnimation = path;
      currentAnimationManager();
    }
    void changeRotation(float rotation){
      animations[pKey].rotation = rotation;
    }
  };
    // Path of the animation expects no .png and no Assets/ just the name of the file
    class player{
        public:
        float xCord;
        float yCord;
        int width = 64; // Rect
        int height = 64; // Rect
        float speedX = 0.00f;
        float speedY = 0.00f;
        Vector2 destRecPos = {0.0f,0.0f};
        std::string currentAnim;
        int direction = 0; // 0 = up , 1 = left, 2 = right, 3 = down
        playerAnimations playerAnims;
        Texture2D playerSprite;
        Vector2 sourceRecPos; 
        std::vector<std::vector<int>> collisionIDsMap;
        Rectangle playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        int health; 
        void draw();
        void update();
        void update(std::vector<std::vector<int>> collisionIDs);
        void movement();
        bool mapCollision(std::vector<std::vector<int>> collisionIDs);
        player(){
          std::vector<std::string> iPaths;
          iPaths.push_back("Player/base/Base_Idle");
          iPaths.push_back("Player/hair/Base_Idle_Hair_3");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Shoes_1");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Pants_1");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Gloves_1");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Chest_1");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Hat_1");
          iPaths.push_back("Player/armor/06_fateful/Base_Idle_Fateful_Chest_1A");
          iPaths.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Idle_EvolSix_1");
          iPaths.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Idle_EvolSix_2");
          playerAnims.addAnimation("Base_Idle", width, height, iPaths);
          std::vector<std::string> iPaths1;
          iPaths1.push_back("Player/base/Base_Attack");
          iPaths1.push_back("Player/hair/Base_Attack_Hair_3");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Shoes_1");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Pants_1");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Gloves_1");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Chest_1");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Hat_1");
          iPaths1.push_back("Player/armor/06_fateful/Base_Attack_Fateful_Chest_1A");
          iPaths1.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Attack_EvolSix_1");
          iPaths1.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Attack_EvolSix_2");
          playerAnims.addAnimation("Base_Attack", width, height, iPaths1);
          std::vector<std::string> iPaths2;
          iPaths2.push_back("Player/base/Base_Walk");
          iPaths2.push_back("Player/hair/Base_Walk_Hair_3");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Shoes_1");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Pants_1");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Gloves_1");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Chest_1");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Hat_1");
          iPaths2.push_back("Player/armor/06_fateful/Base_Walk_Fateful_Chest_1A");
          iPaths2.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Walk_EvolSix_1");
          iPaths2.push_back("Player/weapons/01_Standard Weapon/6th Evolution/Weapon_Walk_EvolSix_2");
          playerAnims.addAnimation("Base_Walk", width, height,iPaths2);
          playerAnims.addAnimation("Base_Dead", width, height);
          playerAnims.switchAnimation("Base_Idle");

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
        void changeRotation1(float rotation){
          playerAnims.changeRotation(rotation);
        }
        // void stateManager();    
    };
    void player::movement(){
      bool isRight = false;
      bool isLeft = false;
      bool vert = false;
      if(IsKeyDown(KEY_RIGHT) ) {
        isRight = true;
        speedX = 2.00f;
        direction = 2;
        if(vert == false){
            changeRotation1(0.00f);
          }
        if(currentAnim != "Player/base/Base_Walk" && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Walk");
          currentAnim = "Player/base/Base_Walk";
        }
        }
        else if(IsKeyDown(KEY_LEFT)){
          if(vert == false){
            changeRotation1(0.00f);
          }
          isLeft = true;
        speedX = -2.00f;
        direction = 1;
        if(currentAnim != "Player/base/Base_Walk" && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Walk");
          currentAnim = "Player/base/Base_Walk";
        }
        }
        if(IsKeyDown(KEY_DOWN)){
          vert = true;
        speedY = 2.00f;
        direction = 3;
        if(currentAnim != "Player/base/Base_Walk" && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Walk");
          currentAnim = "Player/base/Base_Walk";
        }
        }
        else if(IsKeyDown(KEY_UP)){
          vert = true;
       speedY = -2.00f;
        direction = 0;
        if(currentAnim != "Player/base/Base_Walk" && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Walk");
          currentAnim = "Player/base/Base_Walk";
        }
        }
        if(IsKeyDown(KEY_SPACE)){
          switchAnimation("Player/base/Base_Attack");
          currentAnim = "Player/base/Base_Attack";
        }
        if(isRight == false && isLeft == false){
          changeRotation1(0.00f);
        }
        if(isRight == false && isLeft == false && vert == false && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Idle");
          currentAnim = "Player/base/Base_Idle";
        }
       mapCollision(collisionIDsMap);
        
        destRecPos.x = destRecPos.x + speedX;
        destRecPos.y = destRecPos.y + speedY;
        playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        // set poisition of the player in the animation manager using set_position
        playerAnims.currentAnimationManager();
        playerAnims.animations[playerAnims.pKey].set_position(destRecPos.x, destRecPos.y);
    }
  void player::update(){
    movement();
    currentAnim = playerAnims.currentAnimationPath();
  //  draw();
  }
  void player::update(std::vector<std::vector<int>> collisionIDs){
    speedX = 0.00f;
    speedY = 0.00f;
    collisionIDsMap = collisionIDs;
    movement();
    currentAnim = playerAnims.currentAnimationPath();
  //  draw();
  }
  
  void player::draw(){
    playerAnims.draw(destRecPos.x, destRecPos.y, direction);
  } 
  bool player::mapCollision(std::vector<std::vector<int>> collisionIDs){
   // std::clog<<"We are in the collsiion" << std::endl;
   // std::clog << " size of collision map " << collisionIDs.size() << std::endl;
   // std::clog << "size y of collision map " << collisionIDs[0].size() << std::endl;
    bool isColliding = false;
  
    //int playerX = destRecPos.x / 16; // player cordinates to tile map cordiantes
    // int playerY = destRecPos.y / 16;
    int playerX = (destRecPos.x + speedX) / 16; // player cordinates to tile map cordiantes
    int playerY = (destRecPos.y + speedY) / 16;
    std::clog << "player x " << playerX << " player y " << playerY << std::endl;
    std::clog << "collision vector at player x " << collisionIDs[playerY][playerX] << std::endl;
    // Later Change collision Code as this is garbage
    if(collisionIDs[playerY][playerX] != 0){ // check the tile cord against the tile map in each direction and move the player back if they are colliding by getting the animation direction
      isColliding = true;
      if(speedX > 0 || speedX < 0){
        speedX = 0;
      }
      if(speedY > 0 || speedY < 0){
        speedY = speedY = 0;
      }
      std::clog << "collision" << std::endl;
    }
    return isColliding;
  }
  
};







#endif