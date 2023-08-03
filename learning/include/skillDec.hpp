
#ifndef skills_h
#define skills_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "json.hpp"
#include <fstream>
#include <sstream>
namespace skills_NS{
class skill{
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
      std::string typeOfSkill; // Possible Values: "Square", "Cirlce", "Line", "Buff"
      float rotation = 0.00f;
      Vector2 position = {0.00f, 0.00f};
      Rectangle frameRec = {0.00f, 0.00f, 0.00f, 0.00f};
      Texture2D texture1;
      std::string path;
      Rectangle sourceRec = {0.00f, 0.00f, 0.00f, 0.00f};
      Texture2D skillIcon;
      skill(std::string path, std::string StypeOfSkill){
        textures.push_back(LoadTexture(("Assets/player/03_FX/" + path).c_str()));
        texture1 = textures[0];
        frameRec.width = fWidth;
        frameRec.height = fHeight;
        typeOfSkill = StypeOfSkill;
       }
       skill(std::string path , std::string StypeOfSkill, std::string iconPath){
        textures.push_back(LoadTexture(("Assets/player/03_FX/" + path).c_str()));
        texture1 = textures[0];
        frameRec.width = fWidth;
        frameRec.height = fHeight;
        typeOfSkill = StypeOfSkill;
        skillIcon = LoadTexture(("Assets/player/icons/" + iconPath).c_str());
       }
     ~skill(){
        for(int i = 0; i < textures.size(); i++){
          UnloadTexture(textures[i]);
        }
      }
    };
  std::vector<skill> getAllSkills(){
    std::vector<skill> skills; 
    skills.push_back(skill("Skill_Cleave_FX.png", "Circle","369_BattleAxe.png"));
    skills.push_back(skill("Skill_AncientSpear_1_FX.png", "Line","65_Light_Grimoire.png"));
    skills.push_back(skill("Skill_BringerOfChaos_FX.png", "Line", "73_Darkness_Grimoire.png"));
    skills.push_back(skill("Skill_CelestialJudgement_FX.png", "Line", "72_Light_Spear.png")); 
    skills.push_back(skill("Skill_CutTheSky_FX.png", "Circle", "386_Lightning_Battleaxe.png"));
    skills.push_back(skill("Skill_GroundStomp_FX.png", "Line", "37_Earth_III.png"));
    skills.push_back(skill("Skill_MagmaReaction_FX.png", "Line", "01_Fire_Grimoire.png"));
    skills.push_back(skill("Skill_SoulFeast_FX.png", "Line", "73_Darkness_Grimoire.png"));
    skills.push_back(skill("Skill_Zayvris_FX.png", "Line", "25_Cloud_Grimoire.png"));
    skills.push_back(skill("Skill_Whirlwind_FX.png", "Line", "462_Air_Tornado.png"));
    return skills;    
  }
};
  #endif