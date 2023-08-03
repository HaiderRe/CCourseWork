#ifndef sounds_h
#define sounds_h
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
namespace sounds_NS{
    class sounds{
        public:
        Music sfx;
        bool shouldPlay = false;
        sounds(std::string path){
            sfx = LoadMusicStream(("Assets/sounds/" + path).c_str());
        }
        void playSound(){
            PlayMusicStream(sfx);
        }
     };
     class soundManager{
        public:
        std::vector<sounds> soundsVector;
        std::vector<Music> soundsMusic;
        soundManager(){
            
        }
        void addSound(sounds sound){ 
            soundsVector.push_back(sound);
            soundsMusic.push_back(sound.sfx);
        }
     };
     class soundAddManager{
        public: 
        int soundIndex;
        soundManager* soundManagerObject;
        soundAddManager(int index, soundManager* soundManagerObject){
            soundIndex = index;
            this->soundManagerObject = soundManagerObject;
        }
        void addSound(std::string path){
            soundManagerObject->addSound(sounds(path));
        }
        void getSoundToAdd(){ // Call this first 
                std::ifstream filestream("Assets/sounds/sounds.json");
                std::stringstream buffer;
                buffer << filestream.rdbuf();
                std::string json_string = buffer.str();
                json j = json::parse(json_string);
                for (json::iterator it = j["sounds"].begin(); it != j["sounds"].end(); ++it) {
                 if ((*it)["id"] == soundIndex) {
                 std::string soundPath = (*it)["path"];
                 addSound(soundPath);
                 }
                }
            }
        }; 
     };
#endif