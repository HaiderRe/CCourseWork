#include <iostream> 
#include <string>
#include <cmath>
#include "include/raylib.h"
#include "include/rlgl.h"
#include "include/raymath.h"
#include <vector>
#include "include/xml_parser.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
struct tile{
    int coordx;
    int coordy; 
    bool is_black = false;
    Color col = RED;
    Texture2D c_texture;
};

class tilemap{
    public:
    int width;
    int height;
    int x_size; 
    int y_size; 
    int pixel_size;
    tile *arr_tiles; // Change this to a Vector of tile vectors // Easier
    void draw();
    void set_width_height(int w, int h); 
    void set_width_height_of_arr(int x, int y); 
    // void read_from_file(std::string c_map); //c_map being the map to load // +1 No need to handle this here.
};
void tilemap::draw(){
   Color col = RED;
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            //arr_tiles[i*y_size+j].coordx;
            if(i % 2 == 0 && j % 2 == 0){
               arr_tiles[i*y_size+j].col = GREEN;
            }
            else if(!(i % 2 == 0) && !(j % 2 == 0)){
                arr_tiles[i*y_size+j].col = GREEN;
            }
            else{
                arr_tiles[i*y_size+j].col = RED;
            }
            if(j == 59 && i == 34){
                arr_tiles[i*y_size+j].col = BLACK;
            }
          if(arr_tiles[i*y_size+j].is_black){
            arr_tiles[i*y_size+j].col = BLACK;
          }
            DrawRectangle(arr_tiles[i*y_size+j].coordx, arr_tiles[i*y_size+j].coordy, width, height, arr_tiles[i*y_size+j].col);
            DrawCircle(arr_tiles[i*y_size+j].coordx, arr_tiles[i*y_size+j].coordy, 3.00f,BLUE);
            
        }
    }
}
void tilemap::set_width_height_of_arr(int w, int h){  
    // H = Height (of 2D Array)
    // W = Width (Of 2D Array)
    arr_tiles = new tile[w*h];
    x_size = w; 
    y_size = h;
}
void tilemap::set_width_height(int w, int h){ 
    //sets widths of height of each tile  
    int x_offset = GetScreenWidth() / 2; // X_offset, so that the tiles start from an offset of // (0,0) origin - x_offset ( - left) 
    int y_offset = GetScreenHeight() /2; // Y_offset, so that the tiles start from an offset of // (0,0) origin - Y_offset (- up) 
    width = w; 
    height = h;
    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            arr_tiles[i*y_size+j].coordx = ((width * j) - x_offset);
            arr_tiles[i*y_size+j].coordy = ((height * i) - y_offset); 
            //std::cout << "x coord " + std::to_string(arr_tiles[i * y_size + j].coordx) << std::endl; Debugging
            //std::cout << "y coord " + std::to_string(arr_tiles[i * y_size + j].coordy) << std::endl; Debugging 
        }
    }
 //   width = (GetScreenWidth()/ x_size);
   // height = (GetScreenHeight() / y_size);
}
/*void tilemap::read_from_file(std::string c_map){
    c_map = c_map;
}
*/


    

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    tilemap default_map; 
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Camera2D cam = {0};
    cam.zoom = 1.0f;
    cam.target = Vector2{ 00.0f, 00.0f };
    cam.offset = Vector2{ screenWidth/2.0f, screenHeight/2.0f };
    cam.rotation = 0.0f;
    int y_size = default_map.y_size;
    int y = 0;
    int x  = 0;
    int oldx = 0; 
    int oldy = 0;
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    default_map.set_width_height_of_arr(64,64);
    default_map.set_width_height(32, 32);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) ToggleFullscreen();
        // Update
        
      if(IsKeyDown(KEY_RIGHT) ) {
        cam.target.x = cam.target.x + 4.00f;
        }
        else if(IsKeyDown(KEY_LEFT)){
            
          cam.target.x = cam.target.x - 2.00f;
        }
        if(IsKeyDown(KEY_DOWN)){
      
          cam.target.y = cam.target.y + 4.00f;
        }
        else if(IsKeyDown(KEY_UP)){
           cam.target.y = cam.target.y - 2.00f;
        }
        if(IsKeyPressed(KEY_SPACE)){
            std::cout << "x " + std::to_string(x) + " y " + std::to_string(y) << std::endl;
        } 
        if(x > 63){
            x = 0; 
            y = y +  1;
        } 
     //  default_map.arr_tiles[oldx*y_size+oldy].is_black = false;
        default_map.arr_tiles[0*y_size+2171].is_black = true;
      //  oldx = x;
      //  oldy = y; 
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();


            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
           BeginMode2D(cam);
            default_map.draw();
          EndMode2D();

            
            

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