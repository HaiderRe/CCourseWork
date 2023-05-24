#ifndef game_renderer_h
#define game_renderer_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
#include "enemy_objects.hpp"
namespace game_renderer_h{
    struct textureWrapper{ //Needed as we will be Dynamically DeAlloc textures using different methods 
    Texture2D texture;
    bool isLoaded = true; 
    };
    struct gameObject{
        Texture2D textureWrapper;
        float xCord;
        float yCord;
        Rectangle test_rect;
        Color testColor;
        int width;
        int height;

    };
    class game_renderer{
    public:
    std::vector<textureWrapper> textureDeAlloc;
    std::vector<projectile> projectilesEnemy;
    gameObject jameObject;
    void draw(gameObject jameObject);
    bool DeAlloc();
    
    
}; 
void game_renderer::draw(gameObject jameObject){
    DrawRectangle(jameObject.xCord, jameObject.yCord, jameObject.width, jameObject.height, jameObject.testColor);

}
bool game_renderer::DeAlloc(){
    for(textureWrapper &textureToBe : textureDeAlloc ){
        if(textureToBe.isLoaded == true){
            UnloadTexture(textureToBe.texture);
        }
    }
    for(projectile &proj : projectilesEnemy){
        projectile* ptr = &proj;
        delete ptr;
        ptr = nullptr;
    }
    return true;
}
class state_manager{
    public:
    tilemap currentTilemap;
 };
}
#endif