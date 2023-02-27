#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
class tile_map_nodes{
    tile_map_nodes *parent_node;
    int width;
    int height;
};
class file_to_read{
    int width; 
    int height; 
    bool read;
    int nextlayerid;
    int pixel_width;
    int pixel_height;
    std::string *tilesets;
    public: 
     void read_file(std::string path);
};
void read_file(std::string path){
    std::ifstream tilemap; 
    tilemap.open(path);
    if(tilemap){

    }

}