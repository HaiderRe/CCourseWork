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
    Color playerColor = WHITE;
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
    void changeColor(Color aColor){
      animations[pKey].playerColor1 = aColor;
      for(int i = 0; i < animations.size(), i++;){
        animations[i].setColor(aColor);
      }
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
      std::string currentTypeOfSkill; // Possible Values: "Square", "Cirlce", "Line", "Buff",  "LineChunk"
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
      int lineChunks = 0;
      Vector2 currentPos = {0.00f, 0.00f};
      Vector2 lerpCurrentPos = {0.00f, 0.00f};
      bool testingBool = false;
       float progressStep;
      Camera2D camera1;
      Vector2 mousePos = {0.00f, 0.00f};
      Vector2 FMousePos = {0.00f, 0.00f};
      Vector2 intialCamOffset = {0.00f, 0.00f};
      Vector2 FPlayerPos = {0.00f, 0.00f};
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
      int GetCollisionBetweenEnemies(Rectangle aRect){
        return 0; 
      }
      int hitBoxDrawSquare(Rectangle aEnemyRect){
       Rectangle hitBox =  {FMousePos.x, FMousePos.y, 128, 128};
       if(CheckCollisionRecs(hitBox, aEnemyRect)){
        return 1;
      }
      else{
        return 0;
      }
      return 0;
      }
      int hitBoxDrawCircle(Rectangle aEnemyRect){
        return 0;
      }
      int hitBoxDrawLine(Rectangle aEnemyRect){ // 
      Rectangle destRec = {lerpCurrentPos.x - 16, lerpCurrentPos.y - 16, 32, 32}; //Projectile Dest Rect
      std::clog << "lerpCurrentPos = " + std::to_string(lerpCurrentPos.x) + " " + std::to_string(lerpCurrentPos.y) << std::endl;
      std::clog << "aEnemyRect = " + std::to_string(aEnemyRect.x) + " " + std::to_string(aEnemyRect.y) << std::endl;
      if(CheckCollisionRecs(destRec, aEnemyRect)){
        return 1;
      }
      else{
        return 0;
      }
      return 0;
      }
      void hitBoxDrawLineDraw(){
        Rectangle destRec = {(lerpCurrentPos.x - 16), (lerpCurrentPos.y - 16), 32, 32};
        DrawRectangleLines(destRec.x, destRec.y, 32, 32, GREEN);
      }
      int hitBoxDrawBuff(Rectangle aEnemyRect){
        return 0;
      }
      int hitBoxDrawLineChunk(Rectangle aEnemyRect){
        int AmountOfChunks = 5; // Amount of Chunks
    static std::vector<Vector2> chunkPositions(AmountOfChunks); // Retain values 
     static std::vector<int> chunkFrames(AmountOfChunks, 0); // Static retains the values 
        // Initialize the chunk positions 
        for(int i = 0; i < AmountOfChunks; ++i){
            float progress = (float)i / (AmountOfChunks - 1);
            chunkPositions[i] = {
                FPlayerPos.x + progress * (FMousePos.x - FPlayerPos.x),
                FPlayerPos.y + progress * (FMousePos.y - FPlayerPos.y)
            };
        } 
        for(int j = 0; j< AmountOfChunks; j++){
          Rectangle destRec = {chunkPositions[j].x, chunkPositions[j].y, 32, 32};
          if(CheckCollisionRecs(destRec, aEnemyRect)){
            return 1;
          }
        }
        return 0;
      }
      //Enemies Call this function with their rectangle
      int hitBoxDecide(Rectangle aEnemyRect){ 
        int hit = 0;
        std::clog << "type of skill = " + currentTypeOfSkill << std::endl;
        if(isCastingN == false){
          return 0;
        }
        if(currentTypeOfSkill == "Square"){
         hit = hitBoxDrawSquare(aEnemyRect);
        }
        else if(currentTypeOfSkill == "Circle"){
       hit =  hitBoxDrawCircle(aEnemyRect);
        }
        else if(currentTypeOfSkill == "Line" ){
         hit = hitBoxDrawLine(aEnemyRect);
        }
        else if(currentTypeOfSkill == "Buff"){
          hit = hitBoxDrawBuff(aEnemyRect);
        }
        else if(currentTypeOfSkill == "LineChunk"){
          hit = hitBoxDrawLineChunk(aEnemyRect);
        }
        return hit;
      }

      void drawDecide(Camera2D aCamera){
        camera1 = aCamera;
        int extraFrames = extraFrames1;
      //  std::clog << " in draw Decided"  + std::to_string(isCastingN) << std::endl;
        if(currentTexture.id == 0){
          // std::clog << "current texture is 0" << std::endl;
          return;
        }
        if(currentAnim == "Player/base/Base_Attack1"){
          drawAOneFrame();
          std::clog << "DrawAoneFrame" << std::endl;
          return;
        }
        if(isCastingN && isDone == false){ // 
         // std::clog << " is casting" << std::endl;
         drawFx(extraFrames);
        }
      }
    void SDrawLine(int extraFrames){
    if(FMousePos.x == 0 && FMousePos.y == 0){
      Vector2 tempVector = GetMousePosition();
        tempVector.x += 16;
       tempVector.y += 16;
        FMousePos = GetScreenToWorld2D(tempVector, camera1);
        FPlayerPos.x = position.x + 32;
        FPlayerPos.y = position.y + 32;  // Store the initial player position when starting the animation.
    }  

    int width = 32;
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

    // Calculate the progress between 0 (beginning) and 1 (end).
    float progress = 1;
    if(maxFrames + extraFrames - 1 == 0){
      progress = 1;
    }
    else{
      progress = (float)currentFrame1 / (float)(maxFrames + extraFrames - 1);
    }
// Intrpolate between the player's position and the mouse's position based on the progress.
Vector2 interpolatedPos = {
    FPlayerPos.x + progress * (FMousePos.x - FPlayerPos.x),
    FPlayerPos.y + progress * (FMousePos.y - FPlayerPos.y)
};


    Rectangle destRec = {interpolatedPos.x , interpolatedPos.y , width, width};

    DrawTexturePro(currentTexture, frameRec1, destRec, {float(width/2), float(width/2)},  calcRotation(camera1) * (180.0f/PI), RED);
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
      void drawLine(int extraFrames){
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
            FMousePos = {0.00f, 0.00f};
          }
        }
        DrawTexturePro(currentTexture, frameRec1, destRec, {float(width/2), float(width/2)},  calcRotation(camera1) * (180.0f/PI), RED);
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
void DrawLineChunk(int extraFrames){
    int AmountOfChunks = 5; // Amount of Chunks
    static std::vector<Vector2> chunkPositions(AmountOfChunks); // Retain values 
     static std::vector<int> chunkFrames(AmountOfChunks, 0); // Static retains the values 
    
    if(FMousePos.x == 0 && FMousePos.y == 0){
        Vector2 tempVector = GetMousePosition();
        tempVector.x += 16;
        tempVector.y += 16;
        FMousePos = GetScreenToWorld2D(tempVector, camera1);
        FPlayerPos.x = position.x + 32;
        FPlayerPos.y = position.y + 32;  
        
        // Initialize the chunk positions 
        for(int i = 0; i < AmountOfChunks; ++i){
            float progress = (float)i / (AmountOfChunks - 1);
            chunkPositions[i] = {
                FPlayerPos.x + progress * (FMousePos.x - FPlayerPos.x),
                FPlayerPos.y + progress * (FMousePos.y - FPlayerPos.y)
            };
        }
    }  

    int width = 32;
    int maxFrames = currentTexture.width / 64;
    
    for(int i = 0; i < AmountOfChunks; ++i){
        Rectangle frameRec1 = {64 * chunkFrames[i], 0, 64, 64};

        frames1++;
        if(frames1 > (60/frameSpeed1)){
            frames1 = 0;
            chunkFrames[i]++;
            if(chunkFrames[i] >= maxFrames + extraFrames){
                chunkFrames[i] = 0;
                isDone = true;
                FMousePos = {0.00f, 0.00f};
            }
        }

        Rectangle destRec = {chunkPositions[i].x , chunkPositions[i].y , width, width};

        DrawTexturePro(currentTexture, frameRec1, destRec, {float(width/2), float(width/2)},  calcRotation(camera1) * (180.0f/PI), WHITE);
    }
    if(isDone){
      for(int i = 0; i < AmountOfChunks; ++i){
        chunkFrames[i] = 0;
        chunkPositions[i] = {0.00f, 0.00f};
      }
    }
}

void LerpSDrawLine(int extraFrames){
  std::clog << "curentPos Before = " + std::to_string(currentPos.x) + " " + std::to_string(currentPos.y) << std::endl;
  int maxFrames = currentTexture.width / 64;
    if(FMousePos.x == 0 && FMousePos.y == 0){
      Vector2 tempVector = GetMousePosition();
      tempVector.x += 16;
      tempVector.y += 16;
      FMousePos = GetScreenToWorld2D(tempVector, camera1);
      FPlayerPos.x = position.x + 32;
      FPlayerPos.y = position.y + 32;  
      currentPos = FPlayerPos; 
      
      
      // Determine the step size for each fram
      progressStep = 1.0f / ((60/frameSpeed1) * (maxFrames + extraFrames)); 
    }
    int width = 32;
    Rectangle frameRec1 = {64 * currentFrame1, 0, 64, 64};
    testingBool = true;

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

    // Increment currentPos 
    currentPos.x += progressStep * (FMousePos.x - FPlayerPos.x);
    currentPos.y += progressStep * (FMousePos.y - FPlayerPos.y);
    lerpCurrentPos = {currentPos.x, currentPos.y};
    
    Rectangle destRec = {currentPos.x, currentPos.y, width, width};

    DrawTexturePro(currentTexture, frameRec1, destRec, {float(width/2), float(width/2)}, calcRotation(camera1) * (180.0f/PI), WHITE);
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
          isDone = true;
          return;
          drawCircle();
        }
        else if(currentTypeOfSkill == "Line"){
          LerpSDrawLine(extraFrames);
        }
        else if(currentTypeOfSkill == "Buff"){
          return;
          drawBuff();
        }
        else if(currentTypeOfSkill == "LineChunk")
        DrawLineChunk(extraFrames);
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
       // std::cout<< " in draw function for skillSlots" << std::endl;
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
        int colorCountDown = -1;
        float xCord;
        float yCord;
        int width = 64; // Rect
        int height = 64; // Rect
        float speedX = 0.00f;
        float speedY = 0.00f;
        Vector2 destRecPos = {0.0f,0.0f};
        std::string currentAnim;
        int direction = 0; // 0 = up , 1 = left, 2 = right, 3 = down
        Color playerColor = WHITE;
        playerAnimations playerAnims;
        Texture2D playerSprite;
        Vector2 sourceRecPos; 
        std::vector<std::vector<int>> collisionIDsMap;
        Rectangle playerRect = {destRecPos.x, destRecPos.y, float(width), float(height)};
        float health = 5.00f; 
        Camera2D camera1;
        void draw();
        void update();
        void update(std::vector<std::vector<int>> collisionIDs);
        void movement();
        void drawOffCamera();
        int takeDamage();
        int takeDamage(float damagePoints);
        int takeDamage(float damagePoints, int direction);
        int takeDamage(float damagePoints, Rectangle aPreviousEnemyRectangle); //For None-Slimes
        int takeDamage(float damagePoints, Vector2 aPreviousEnemy); //For Slimes

        int testingFunctionDraw(){
                float offsetX = 0.0f;
                float offsetY = 0.0f;
                int width = 8;
                int height = 8;
                if(direction == 0){
                    offsetX += 24.0f;
                    offsetY += 00.0f;
                    height = 16;
                    width = 32;
                }
                if(direction == 1){
                    offsetY += 32.0f;
                    offsetX += 8.00;
                    width = 32;
                }
                if(direction == 2){
                    offsetX += 32.0f;
                    offsetY += 32.0f;
                    width = 32;
                }
                if(direction == 3){
                    offsetY += 32.0f;
                    offsetX += 24.0f;
                    width = 32;
                    height = 16;
                }
                Rectangle weaponHitBox = {destRecPos.x + offsetX, destRecPos.y + offsetY, width, height};
                DrawRectangleLines(weaponHitBox.x, weaponHitBox.y, weaponHitBox.width, weaponHitBox.height, RED);
        }
        bool mapCollision(std::vector<std::vector<int>> collisionIDs);
        fxPlayer fxPlayerObject;
        int fxDamage = 1;
        int weaponDamage = 1;
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
        void changeColor(Color aColor){
          playerAnims.playerColor = aColor;
          playerAnims.changeColor(aColor);
        }
        // void stateManager();    
    };
    int player::takeDamage(){
      health = health - 1;
      playerColor = RED;
      colorCountDown = 60;
      return 0;
    }
    int player::takeDamage(float damagePoints){
      health = health - damagePoints;
      playerColor = RED;
      colorCountDown = 60;
      return 0;
    }
    int player::takeDamage(float damagePoints, int direction){
      health = health - damagePoints;
      playerColor = RED;
      colorCountDown = 60;
      Vector2 nextDestRecPos = {destRecPos.x, destRecPos.y};
      int knockBack = 6;
      if(direction == 0){
        nextDestRecPos = {destRecPos.x, destRecPos.y + knockBack};
      }
      else if(direction == 1){
        nextDestRecPos = {destRecPos.x + knockBack, destRecPos.y};
      }
      else if(direction == 2){
        nextDestRecPos = {destRecPos.x - knockBack, destRecPos.y};
      }
      else if(direction == 3){
        nextDestRecPos = {destRecPos.x, destRecPos.y - knockBack};
      }
      if(collisionIDsMap[nextDestRecPos.y/16][nextDestRecPos.x/16] == 0){
        destRecPos = nextDestRecPos;
      }
      return 0;
    }
    int player::takeDamage(float damagePoints, Rectangle aPreviousEnemyRectangle){
      health = health - damagePoints;
      playerColor = RED;
      colorCountDown = 60;
      Vector2 nextDestRecPos = {destRecPos.x, destRecPos.y};
      int knockBack = 6;
      Vector2 enemyCenter = {0.00f,0.00f};
       enemyCenter.x = aPreviousEnemyRectangle.x + aPreviousEnemyRectangle.width / 2;
       enemyCenter.y = aPreviousEnemyRectangle.y + aPreviousEnemyRectangle.height / 2;
       Vector2 direction = {0.00f, 0.00f};
       direction.x = destRecPos.x - enemyCenter.x;
       direction.y = destRecPos.y - enemyCenter.y;
       float length = sqrt(direction.x * direction.x + direction.y * direction.y);
       if (length != 0) { 
         direction.x /= length;
         direction.y /= length;
       }
       direction.x *= knockBack;
       direction.y *= knockBack;
       nextDestRecPos = {0.00f, 0.00f};
       nextDestRecPos.x = destRecPos.x + direction.x;
       nextDestRecPos.y = destRecPos.y + direction.y;
         if(collisionIDsMap[nextDestRecPos.y/16][nextDestRecPos.x/16] == 0){
         destRecPos = nextDestRecPos;
       }
       return 0;
    }
    int player::takeDamage(float damagePoints, Vector2 aPreviousEnemy){
      health = health - damagePoints;
      playerColor = RED;
      colorCountDown = 60;
      Vector2 nextDestRecPos = {destRecPos.x, destRecPos.y};
      int knockBack = 6;
      Vector2 enemyCenter = {0.00f,0.00f};
       enemyCenter.x = aPreviousEnemy.x;
       enemyCenter.y = aPreviousEnemy.y;
       Vector2 direction = {0.00f, 0.00f};
       direction.x = destRecPos.x - enemyCenter.x;
       direction.y = destRecPos.y - enemyCenter.y;
       float length = sqrt(direction.x * direction.x + direction.y * direction.y);
       if (length != 0) { 
         direction.x /= length;
         direction.y /= length;
       }
       direction.x *= knockBack;
       direction.y *= knockBack;
        nextDestRecPos = {0.00f, 0.00f};
       nextDestRecPos.x = destRecPos.x + direction.x;
       nextDestRecPos.y = destRecPos.y + direction.y;
         if(collisionIDsMap[nextDestRecPos.y/16][nextDestRecPos.x/16] == 0){
         destRecPos = nextDestRecPos;
       }
       return 0;
    }
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
       // std::clog << "Actual player pos = " << destRecPos.x << " " << destRecPos.y << std::endl;
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
    changeColor(playerColor);
    if(colorCountDown > -1){
      colorCountDown = colorCountDown - 1;
      if(colorCountDown < 0){
        playerColor = WHITE;
        colorCountDown = -1;
      }
    }
    
    playerAnims.draw(destRecPos.x, destRecPos.y, direction);
    skillManagerObject.draw(camera1);
    skillManagerObject.fxPlayerObject.hitBoxDrawLineDraw();
    testingFunctionDraw();
    //playerColor = WHITE;
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
    if(playerX < 0 || playerY < 0 || playerY >= collisionIDs.size() || playerX >= collisionIDs[0].size()){
    return false;
    }
    if(collisionIDs[playerY][playerX] != 0){ // check the tile cord against the tile map in each direction and move the player back if they are colliding by getting the animation direction
      isColliding = true;
      if(speedX > 0 || speedX < 0){
        speedX = 0;
      }
      if(speedY > 0 || speedY < 0){
        speedY = 0;
      }
    //  std::clog << "collision" << std::endl;
    }
    return isColliding;
  }
  
};







#endif