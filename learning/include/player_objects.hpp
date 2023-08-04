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
#include "dialogue.hpp"
#include "skillDec.hpp"
using namespace skills_NS;
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
    void currentAnimationManager(){ // This finds the current animation in the animation manager 
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
    class fxPlayer{
      public:
      std::vector<Texture2D> textures;
      int currentFrame = 0;
      int frames = 0; 
      int frameSpeed = 6;
      int amount_of_frames = 4;
      int fWidth = 64; // Width of the source frame
      int fHeight = 64; // Height of the source frame
      int sWidth = 64;
      int sHeight = 64;
      float rotation = 0.00f;
      Vector2 position = {0.00f, 0.00f};
      Rectangle frameRec = {0.00f, 0.00f, 0.00f, 0.00f};
      Texture2D texture1;
      Texture2D currentTexture;
      std::string currentTypeOfSkill; // Possible Values: "Square", "Cirlce", "Line", "Buff"
      std::string path;
      Rectangle sourceRec = {0.00f, 0.00f, 0.00f, 0.00f};
      std::string currentAnim;
      int current_amount_of_frames = 0;
      int currentFrame1 = 0;
      int frames1 = 0;
      int frameSpeed1 = 6;
      bool isPlaying = false;
      bool isDone = false;
      bool isCastingN = false;
      int cDirection;
      int extraFrames1 = 0;
      Camera2D camera1;
      Vector2 mousePos = {0.00f, 0.00f};
      Vector2 FMousePos = {0.00f, 0.00f};
      Vector2 intialCamOffset = {0.00f, 0.00f};
      fxPlayer(){
        textures.push_back(LoadTexture(("Assets/player/03_FX/Skill_Cleave_FX.png")));
        texture1 = textures[0];
        frameRec.width = fWidth;
        frameRec.height = fHeight;
      }
      void update(std::string cAnim, Vector2 playerPos, int direction){ // Update the animation, cAnim is the current Animation being played, Im thinking of having skills all use the same basic animation of the player and the rest being handled by the fxPlayer 
        cDirection = direction;
        position = playerPos;
        currentAnim = cAnim;
        mousePos = GetMousePosition();
      }
       void update(std::string cAnim, Vector2 playerPos, int direction, Vector2 mousePos2){ // Update the animation, cAnim is the current Animation being played, Im thinking of having skills all use the same basic animation of the player and the rest being handled by the fxPlayer 
        cDirection = direction;
        position = playerPos;
        currentAnim = cAnim;
        mousePos = GetMousePosition();
      }
      void update(Texture2D skillTexture, Vector2 playerPos, int direction, Vector2 mousePos2, std::string typeOfSkill1, bool isCastingN1){ // Update the animation, cAnim is the current Animation being played, Im thinking of having skills all use the same basic animation of the player and the rest being handled by the fxPlayer 
        cDirection = direction;
        position = playerPos;
        currentTexture = skillTexture;
        currentTypeOfSkill = typeOfSkill1;
        mousePos = mousePos2;
        isCastingN = isCastingN1;
      }
      float calcRotation(){
        float x = FMousePos.x - position.x;
        float y = FMousePos.y - position.y;
        float rotation = atan2(y, x); // Use trig to find the rotation
        return rotation;
      }
      float calcRotation(Camera2D camera){
       Vector2 mousePosWorld = GetScreenToWorld2D(FMousePos, camera);
       Vector2 positionWorld = GetScreenToWorld2D(position, camera); 
      float x = mousePosWorld.x - positionWorld.x;
      float y = mousePosWorld.y - positionWorld.y;
      float rotation = atan2(y, x); // Use trig to find the rotation
      return rotation;
      }
      void GetCollisionBetweenEnemies(Rectangle aRect){
        return; 
      }
      void hitBoxDrawSquare(){
       Rectangle hitBox =  {FMousePos.x, FMousePos.y, 128, 128};
       GetCollisionBetweenEnemies(hitBox);
      }
      void hitBoxDrawCircle(){

      }
      void hitBoxDrawLine(){

      }
      void hitBoxDrawBuff(){

      }
      void hitBoxDecide(){
        if(isCastingN == false){
          return;
        }
        if(currentTypeOfSkill == "Square"){
          hitBoxDrawSquare();
        }
        else if(currentTypeOfSkill == "Circle"){
          hitBoxDrawCircle();
        }
        else if(currentTypeOfSkill == "Line"){
          hitBoxDrawLine();
        }
        else if(currentTypeOfSkill == "Buff"){
          hitBoxDrawBuff();
        }
      }

      void drawDecide(Camera2D aCamera){
        camera1 = aCamera;
        int extraFrames = extraFrames1;
        std::clog << " in draw Decided"  + std::to_string(isCastingN) << std::endl;
        if(currentTexture.id == 0){
          std::clog << "current texture is 0" << std::endl;
          return;
        }
        if(currentAnim == "Player/base/Base_Attack1"){
          drawAOneFrame();
          std::clog << "DrawAoneFrame" << std::endl;
          return;
        }
        if(isCastingN && isDone == false){ // 
          std::clog << " is casting" << std::endl;
         drawFx(extraFrames);
        }
      }

      void drawSquare(int extraFrames){
        if(FMousePos.x == 0 && FMousePos.y == 0){
          FMousePos = GetMousePosition();
          intialCamOffset = camera1.offset;
        }
        std::cout << " in draw square" << std::endl;
        Rectangle destRec = {FMousePos.x, FMousePos.y, 128, 128};
        int maxFrames = currentTexture.width / 64;
        Rectangle frameRec1 = {64 * currentFrame1, 0, 64, 64};
        frames1++;
        if(frames1 > (60/frameSpeed1)){
          frames1 = 0;
          currentFrame1++;
          if(currentFrame1 >= maxFrames + extraFrames){
            currentFrame1 = 0;
            isDone = true;
            FMousePos = {0.00f, 0.00f};
          }
        }
        DrawTexturePro(currentTexture, frameRec1, destRec, {64, 64},  calcRotation() * (180.0f/PI), RED);
      }
     void SdrawSquare(int extraFrames){
    if(FMousePos.x == 0 && FMousePos.y == 0){
       FMousePos = GetScreenToWorld2D(GetMousePosition(), camera1);
   }
   int width = 32;
   Rectangle destRec = {FMousePos.x + width/2, FMousePos.y + width/2, width, width};

   int maxFrames = currentTexture.width / 64;
   Rectangle frameRec1 = {64 * currentFrame1, 0, 64, 64};

   frames1++;
   if(frames1 > (60/frameSpeed1)){
       frames1 = 0;
       currentFrame1++;
       if(currentFrame1 >= maxFrames + extraFrames){
           currentFrame1 = 0;
           isDone = true;
           FMousePos = {0.0f, 0.0f};
       }
   }

   DrawTexturePro(currentTexture, frameRec1, destRec, {float(width/2), float(width/2)},  calcRotation(camera1) * (180.0f/PI), RED);
}

      void drawCircle(){}
      void drawLine(){}
      void drawBuff(){} 
      void drawFx(int extraFrames){
        std::cout << " in draw fx " + currentTypeOfSkill << std::endl;
        if(currentTypeOfSkill == "Square"){
          SdrawSquare(extraFrames);
        }
        else if(currentTypeOfSkill == "Circle"){
          drawCircle();
        }
        else if(currentTypeOfSkill == "Line"){
          drawLine();
        }
        else if(currentTypeOfSkill == "Buff"){
          drawBuff();
        }
      }

      void drawAOneFrame(){
        Rectangle destRec = { position.x + 32, position.y + 32, sWidth, sWidth};
        Vector2 origin = { sWidth/2, sWidth/2 };
        frameRec.x = cDirection * sWidth;
        DrawTexturePro(texture1, frameRec, destRec, origin, rotation, WHITE);
      }
      void drawA(){
        if(currentAnim != "Player/base/Base_Attack"){
          frames = 0;
          return;
        }
        std::cout << "is playing at frame " << frames << std::endl;
        std::cout << "current frame is " << currentFrame << std::endl;
        isPlaying = true;
        frames++;
        if (frames >= (60/frameSpeed)){
          frames = 0;
          currentFrame++;
          if (currentFrame >= amount_of_frames){
            isDone = true;
          }
          frameRec.x = currentFrame * sWidth;
        }
        Rectangle destRec = { position.x + 32, position.y + 32, sWidth, sWidth};
        Vector2 origin = { sWidth/2, sWidth/2 };
        DrawTexturePro(texture1, frameRec, destRec, origin, rotation, WHITE);
      }
      ~fxPlayer(){
        std::clog << "In deconstructor of fxPlayer" << std::endl;
        for(int i = 0; i < textures.size(); i++){
          UnloadTexture(textures[i]);
        }
      }
    };
    
  class skillSlots{
      public:
      std::vector<skill> skills;
      std::vector<skill> currentSkills;
      std::vector<skill> equippedSkills;
      void addSkill(std::string path, std::string typeOfSkill){
        skills.push_back(skill(path, typeOfSkill));
      }
      void getAllSkills2(){
        skills = getAllSkills();
      }
      void adminGiveAllSkills(){
        currentSkills = skills;
      }
      void draw(){
        std::cout<< " in draw function for skillSlots" << std::endl;
        Rectangle destRec = { 0, 0, 64, 64};
        Rectangle FrameRec = {0, 0 , 32, 32};
        Color grey = {31, 36, 40, 255};
        for(int i = 0; i < 4; i++){
          destRec.x = (GetScreenWidth()/2 - 128) + (i * 64);
          destRec.y = GetScreenHeight() - 64;
          DrawRectangle(destRec.x, destRec.y, destRec.width, destRec.height, grey); 
          DrawRectangleLines(destRec.x, destRec.y, destRec.width, destRec.height, WHITE); 
          if(equippedSkills.size() > i){
            DrawTexturePro(equippedSkills[i].skillIcon, FrameRec, destRec, {0,0}, 0.00f, WHITE);
          }
        }
      }
    };
    class skillManager{
      public:
      std::vector<skill> skills;
      skillSlots skillSlotsObject;
      int currentSkill;
      std::string currentSkillName;
      bool isCasting = false;
      std::string skillType;
      fxPlayer fxPlayerObject;
      skillManager(){
        skillSlotsObject.getAllSkills2();
        skillSlotsObject.adminGiveAllSkills();
      }
      void addSkill(std::string path, std::string typeOfSkill){
        skills.push_back(skill(path, typeOfSkill));
      }
      void getCurrentSkillSlots(){
        // Fill code later 
      }
      void normalDraw(){
        skillSlotsObject.draw();
      }
      void draw(Camera2D camera100){
        fxPlayerObject.drawDecide(camera100);
      }
      void update(Vector2 playerPos, int direction){
      if(fxPlayerObject.isDone == true){
          fxPlayerObject.isDone = false;
          fxPlayerObject.isCastingN = false;
          isCasting = false;
          currentSkill = -1;
          fxPlayerObject.extraFrames1 = 0;
        }
      if(!isCasting){
        if(IsKeyPressed(KEY_ONE)){
          currentSkill = 0;
          fxPlayerObject.extraFrames1 = 1; // Theortical testing for upgradable skills
        }
        else if(IsKeyPressed(KEY_TWO)){
          currentSkill = 1;
        }
        else if(IsKeyPressed(KEY_THREE)){
          currentSkill = 2;
        }
        else if(IsKeyPressed(KEY_FOUR)){
          currentSkill = 3;
        }
        if(skillSlotsObject.equippedSkills.size() > currentSkill && currentSkill != -1){
          std::cout << " in the if statement" << std::endl;
          currentSkillName = skillSlotsObject.equippedSkills[currentSkill].path;
         Texture2D skillTexture = skillSlotsObject.equippedSkills[currentSkill].textures[0];
          fxPlayerObject.isCastingN = true;
          
          isCasting = true;
          fxPlayerObject.update(skillTexture, playerPos, direction, GetMousePosition(), skillSlotsObject.equippedSkills[currentSkill].typeOfSkill, isCasting);
        }
        else{
          currentSkillName = "None";
          currentSkill = -1;
        }
      }
        
      }
    };
    
    class player{
        public:
        skillManager skillManagerObject;
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
        Camera2D camera1;
        void draw();
        void update();
        void update(std::vector<std::vector<int>> collisionIDs);
        void movement();
        void drawOffCamera();
        bool mapCollision(std::vector<std::vector<int>> collisionIDs);
        fxPlayer fxPlayerObject;
        player(){
          skillManagerObject = skillManager();
          std::vector<std::string> iPaths; // Idle Paths
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
          playerAnims.addAnimation("Base_Idle", width, height, iPaths); // Add the animation to the animation manager 
          std::vector<std::string> iPaths1; // Attack Paths
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
     
          playerAnims.addAnimation("Base_Attack", width, height, iPaths1); // Add the animation to the animation manager
          std::vector<std::string> iPaths2; // Walk Paths
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
          playerAnims.addAnimation("Base_Walk", width, height,iPaths2); // Add the animation to the animation manager
          playerAnims.addAnimation("Base_Dead", width, height); // Add the animation to the animation manager
          playerAnims.switchAnimation("Base_Idle"); // Switch to the idle animation

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
      if(IsKeyDown(KEY_D) ) {
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
        else if(IsKeyDown(KEY_A)){
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
        if(IsKeyDown(KEY_S)){
          vert = true;
        speedY = 2.00f;
        direction = 3;
        if(currentAnim != "Player/base/Base_Walk" && currentAnim != "Player/base/Base_Attack"){
          switchAnimation("Player/base/Base_Walk");
          currentAnim = "Player/base/Base_Walk";
        }
        }
        else if(IsKeyDown(KEY_W)){
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
        if(isRight == false && isLeft == false && vert == false && currentAnim != "Player/base/Base_Attack" && currentAnim != "Player/base/Base_Idle"){
          switchAnimation("Player/base/Base_Idle");
          currentAnim = "Player/base/Base_Idle";
        }
       mapCollision(collisionIDsMap);
        
        destRecPos.x = destRecPos.x + speedX;
        destRecPos.y = destRecPos.y + speedY;
        playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        // set poisition of the player in the animation manager using set_position
        playerAnims.currentAnimationManager();
        playerAnims.animations[playerAnims.pKey].set_position(destRecPos.x, destRecPos.y); // Set the position of the animation manager to the player's position
        
    }
  void player::update(){
 //   fxPlayerObject.update(currentAnim, destRecPos, direction);
    skillManagerObject.update(destRecPos, direction);
    movement();
    currentAnim = playerAnims.currentAnimationPath();
  //  draw();
  }
  void player::update(std::vector<std::vector<int>> collisionIDs){
 //   fxPlayerObject.update(currentAnim, destRecPos, direction);
    skillManagerObject.update(destRecPos, direction);
    speedX = 0.00f;
    speedY = 0.00f;
    collisionIDsMap = collisionIDs;
    movement();
    currentAnim = playerAnims.currentAnimationPath();
  //  draw();
  }
  void player::drawOffCamera(){
   skillManagerObject.normalDraw();
  }
  void player::draw(){
    playerAnims.draw(destRecPos.x, destRecPos.y, direction);
    skillManagerObject.draw(camera1);
   // fxPlayerObject.drawDecide();
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
   // / std::clog << "player x " << playerX << " player y " << playerY << std::endl;
   // / std::clog << "collision vector at player x " << collisionIDs[playerY][playerX] << std::endl;
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