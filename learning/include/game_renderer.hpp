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
namespace game_renderer_h{
    struct gameObject{
        Texture2D texture;
        float xCord;
        float yCord;
        Rectangle test_rect;
        Color testColor;
        int width;
        int height;

    };
    class game_renderer{
    public:
    std::vector<Texture2D> textureDeAlloc;
    gameObject jameObject;
    void draw(gameObject jameObject);
    
    
}; 
void game_renderer::draw(gameObject jameObject){
    DrawRectangle(jameObject.xCord, jameObject.yCord, jameObject.width, jameObject.height, jameObject.testColor);

}

}
#endif