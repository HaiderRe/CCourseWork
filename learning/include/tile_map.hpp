#ifndef tile_map_h
#define tile_map_h
#include <iostream> 
#include <string>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <vector>
namespace tilemap_ns
{
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
               arr_tiles[i*y_size+j].col = GREEN; //GREEN
            }
            else if(!(i % 2 == 0) && !(j % 2 == 0)){
                arr_tiles[i*y_size+j].col = GREEN; //GREEN
            }
            else{
                arr_tiles[i*y_size+j].col = RED; //RED
            }
            if(j == 59 && i == 34){
                arr_tiles[i*y_size+j].col = BLACK; //BLACK
            }
          if(arr_tiles[i*y_size+j].is_black){
            arr_tiles[i*y_size+j].col = BLACK; //BLACK
          }
            DrawRectangle(arr_tiles[i*y_size+j].coordx, arr_tiles[i*y_size+j].coordy, width, height, arr_tiles[i*y_size+j].col);
          //  DrawCircle(arr_tiles[i*y_size+j].coordx, arr_tiles[i*y_size+j].coordy, 3.00f,BLUE);
            
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
}; // namespace name

#endif