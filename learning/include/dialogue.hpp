#ifndef dialogues_h
#define dialogues_h
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
using json = nlohmann::json;
namespace dialogues_NS{
    class dialogues{
        public:
        Texture2D dialogueImage;
        std::string pathToDialogue;
        int dialogueID;
        dialogues(std::string path, std::string pathImage){
            pathToDialogue = path;
            dialogueImage = LoadTexture(pathImage.c_str());
        }
        
     };
     class dialogueManager{
         public:
         std::vector<dialogues> dialoguesVector;
         std::vector<Texture2D> dialogueImages;
         std::string dailogueToBeDisplayed;
         std::string currentDialogueString;
         int currentDialogue = -1; // -1 is None
         int owner = -1; // 0 is player, 1 is NPC (is the current speaker), -1 is null
            dialogueManager(){
                dailogueToBeDisplayed = "null";
                currentDialogueString = "null";
         }
         void update(){
             // Update the dialogue manager Check if button pressed and move dialgoue forward
         }
         void draw(){
             // Draw the dialogue  
         }
         bool addDialogue(dialogues dialogue){ 
             dialoguesVector.push_back(dialogue);
             dialogueImages.push_back(dialogue.dialogueImage);
             return true;
         }
         std::string getDialogueNPC(int dialogueIndex, int owner){ // Returns the dialogue of the NPC
         // Add error handling later
             std::ifstream filestream("Assets/dialogue/npc.json");
             std::stringstream buffer;
             std::string dialogue;
             buffer << filestream.rdbuf();
             std::string json_string = buffer.str();
            nlohmann::json j = nlohmann::json::parse(json_string);
            for (nlohmann::json::iterator it = j["people"].begin(); it != j["people"].end(); ++it) {
            if ((*it)["id"] == owner) {
            for (nlohmann::json::iterator jt = (*it)["dialogues"].begin(); jt != (*it)["dialogues"].end(); ++jt) {
             if ((*jt)["id"] == dialogueIndex) {
                std::string dialogue = (*jt)["text"];
                 return dialogue;
                     } 
                    }
                }
            }
             return "null";
         }
     };
    };
#endif