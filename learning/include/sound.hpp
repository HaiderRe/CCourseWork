#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include "raylib.h"
#include <vector>
#include <string>

class SoundManager{
public:
    static SoundManager& getInstance()
    {
        static SoundManager instance;  
        return instance;
    }

    int loadSound(std::string path)
    {
        std::string fullPath = "Assets/sounds/" + path;
        Sound sound = LoadSound(fullPath.c_str());
        sounds.push_back(sound);
        return sounds.size() - 1; // Return the index of the sound
    }
    void unloadSound(int index){
        if (index >= 0 && index < sounds.size())
        {
            UnloadSound(sounds[index]);
            
        }
    }
    void playSound(int index)
    {
        
        if (index >= 0 && index < sounds.size())
        {
            PlaySound(sounds[index]);
        }
    }

    void unloadAll()
    {
        for (Sound sound : sounds)
        {
            UnloadSound(sound);
        }
        sounds.clear();
    }

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

private:
    SoundManager() {} 
    ~SoundManager()    
    {
        unloadAll();
    }

    std::vector<Sound> sounds;
};

#endif