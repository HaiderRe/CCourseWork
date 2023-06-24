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
#include "tile_map.hpp"
namespace enemy_objects_h_1 {
    class projectile;
};
namespace game_renderer_h_1{
    struct textureWrapper{ //Needed as we will be Dynamically DeAlloc textures using different methods 
    Texture2D texture;
    bool isLoaded = true;  // This is what we need to track whether a texture is loaded or not, this prevents unloading an already loaded texture.
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
    std::vector<enemy_objects_h_1::projectile*> projectilesEnemy;
    gameObject jameObject;
    Camera2D cam;
    void draw(gameObject jameObject);
    bool DeAlloc();
    void init();
    
    
}; 
void game_renderer::init(){
    cam = {0};
    cam.zoom = 2.0f;
    cam.target = Vector2{ 00.0f, 00.0f };
    cam.offset = Vector2{ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    cam.rotation = 0.0f;
}
void game_renderer::draw(gameObject jameObject){
    DrawRectangle(jameObject.xCord, jameObject.yCord, jameObject.width, jameObject.height, jameObject.testColor);

}
bool game_renderer::DeAlloc(){
    for(textureWrapper &textureToBe : textureDeAlloc ){
        if(textureToBe.isLoaded == true){
            UnloadTexture(textureToBe.texture);
        }
    }
    for(enemy_objects_h_1::projectile* proj : projectilesEnemy){
        delete proj;
    }
    return true;
}
class state_manager{
    public:
    tilemap_ns::tilemap currentTilemap;
 };
}
#endif