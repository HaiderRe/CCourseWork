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
    Texture2D c_texture;
};
class tilemap{
    public:
    int width;
    int height;
    int x_size; 
    int y_size; 
    int pixel_size;
    tile *arr_tiles;
    void draw();
    void set_width_height(); 
    void set_width_height_of_arr(int x, int y); 
    void read_from_file(std::string c_map); //c_map being the map to load
};
void tilemap::draw(){
    Color col = RED;
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            //arr_tiles[i*y_size+j].coordx ;
            
            if(i % 2 == 0 && j % 2 == 0){
                col = GREEN;
            }
            else if(!(i % 2 == 0) && !(j % 2 == 0)){
                col = GREEN;
            }
            else{
                col = RED;
            }
            DrawRectangle(arr_tiles[i*y_size+j].coordx, arr_tiles[i*y_size+j].coordy, width, height, col);
        }
    }
}
void tilemap::set_width_height_of_arr(int w, int h){  // H = Height W = Width (Of 2D Array)
    //tile **arr_tiles = new tile*[h];
    arr_tiles = new tile[w*h];
    x_size = w; 
    y_size = h;
}
void tilemap::set_width_height(){
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            arr_tiles[i*y_size+j].coordx = (GetScreenWidth() / x_size * j);
            arr_tiles[i*y_size+j].coordy = (GetScreenHeight() / y_size * i); 
        }
    }
    width = (GetScreenWidth()/ x_size);
    height = (GetScreenHeight() / y_size);
}
void tilemap::read_from_file(std::string c_map){
    c_map = c_map;
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
    default_map.set_width_height_of_arr(40,40);
    default_map.set_width_height();

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
            default_map.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete[] default_map.arr_tiles;
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}