#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"
#include <vector>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
struct tile{
    int coordx;
    int coordy; 
};
class tilemap{
    public:
    int width;
    int height; 
    int pixel_size;
    std::vector<std::vector<tile>> tiles;
    void draw();
};
void tilemap::draw(){
    for(int i = 0; i < tiles.size(); i++){
        for(int j = 0; j < tiles[i].size(); j++){
            tiles[i][j].coordy = (GetScreenHeight() / tiles[i].size()) ;
            tiles[i][j].coordx = GetScreenWidth
     }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    tilemap default_map; 
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}