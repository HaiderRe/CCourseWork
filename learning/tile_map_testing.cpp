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
    int tileID;  
};

class tilemap {
public:
    int width;
    int height;
    int x_size;
    int y_size;
    int pixel_size;
    std::vector<std::vector<tile>> arr_tiles;

    // Reference to xml parser
    const my_xml_parser::file_to_read& parser;

    // Constructor accepts a reference to the xml parser
    tilemap(const my_xml_parser::file_to_read& parser)
        : parser(parser) {
        // Populate arr_tiles with tiles, each having the corresponding tileset texture
        const auto& tileSets = parser.getTileSets();  // Assuming getTileSets() returns tileSets vector
        for (const auto& tileset : tileSets) {
            // Iterate and assign texture to each tile
            // Details depend on your specific logic
        }
    }
};
tilemap::tilemap(const my_xml_parser& parser) {
    const auto& tileSets = parser.getTileSets();
    for (const auto& tileset : tileSets) {
        Texture2D texture = LoadTexture(tileset.getImagePath().c_str());
        // Populate your arr_tiles with tiles having appropriate textures
        // You need to decide on tile placement and orientation
    }
}
void tilemap::draw() {
    for (int i = 0; i < y_size; i++) {
        for (int j = 0; j < x_size; j++) {
            // get the current tile
            tile& currentTile = arr_tiles[i][j];
            Texture2D tileTexture = parser.getTextureForTileID(currentTile.tileID);  //  need to implement getTextureForTileID() in file_to_read
            // draw the tile with the texture
            DrawTexture(tileTexture, currentTile.coordx, currentTile.coordy, WHITE);
        }
    }
}


void tilemap::set_width_height_of_arr(int w, int h){
    arr_tiles.resize(h, std::vector<tile>(w));
    x_size = w; 
    y_size = h;
}

void tilemap::set_width_height(int w, int h){
    int x_offset = GetScreenWidth() / 2;
    int y_offset = GetScreenHeight() / 2;
    width = w; 
    height = h;

    for(int i = 0; i < y_size; i++){
        for(int j = 0; j < x_size; j++){
            arr_tiles[i][j].coordx = ((width * j) - x_offset);
            arr_tiles[i][j].coordy = ((height * i) - y_offset); 
        }
    }
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
      //  default_map.arr_tiles[0*y_size+2171].is_black = true;
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
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}