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
namespace dialogues_NS{
    class dialogues{
        public:
        dialogues(){
            // Dialogues Constructor 

        }
        void update(){
            // Update the dialogues 
        }
        void draw(){
            // Draw the dialogues 
        }
     };
     class dialogueManager{
         public:
         std::vector<dialogues> dialoguesVector;
         dialogueManager(){
             // Dialogue Manager Constructor 
         }
         void update(){
             // Update the dialogue manager 
         }
         void draw(){
             // Draw the dialogue manager 
         }
     };
    };
#endif