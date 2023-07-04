#ifndef xml_parser
#define xml_parser
#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include "rapidxml.hpp"
#include "game_renderer.hpp"
#include "raylib.h"
// #include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "json.hpp"
using json = nlohmann::json;
namespace my_xml_parser{
    /*
class aTileSet{
    public:
    std::vector<std::vector<int>> tileIDs; // Create an 2D Vector of ints to hold the tileIDs of the tilemap.
    int tileWidth;
    int tileHeight;
    aTileSet(std::string path){
        std::string name = path; 
    }
};
*/
class tileset{
    public:
    std::string name;
    int firstGID;
    std::vector<std::vector<int>> tileSetIDs; // Create an 2D Vector of ints to hold the tileIDs of the tilemap.
    int tileWidth;
    int tileHeight;
    int tileCount;
    int imageWidth;
    int imageHeight;
    int columns;
    std::string image;
   // tileset(std::string path){
     //   std::string name = path; 
    //}
};
class file_to_read{
    private:
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<std::vector<int>> tileIDsCollision;  // Vector of a vector of ints containing the tileIDs of a tilemap for collision.
    std::vector<std::string> tileSets;
    std::vector<tileset> tileset_vector;
    game_renderer_h_1::textureWrapper mapTexture;
    int imageWidth;
    int imageHeight;
    int tileColumns;
    int tileMapColumns;
    std::vector<int> collisionIDs;
    std::string tileMapName;
    public:
    file_to_read(std::string ipath){
    path = ipath; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<std::string> tileSets;
    read_xml_file();
    } 
    file_to_read(){
        std::cerr << "file_to_read with no parameters :/" << std::endl;
    }
    bool setCollisionIDs(){
        std::string path = tileMapName + "collision.json"; 
        std::ifstream ifs(path); 

     if(!ifs.is_open()){
            std::cerr << "Error opening file!" << std::endl;
        return false;
         }

    json j;
    ifs >> j;
    std::vector<int> vec;
    if(j.is_array()){
        for(auto& element : j){
            if(element.is_number()){
                vec.push_back(element.get<int>());
            }
            else{
                std::cerr << "Non-integer value in the array, skipping..." << std::endl;
            }
        }
    }
    else{
        std::cerr << "JSON is not an array!" << std::endl;
    }

    // Printing the vector to check the results
    for(auto& num : vec){
        std::cout << num << " " << std::endl;
    }
    std::cout << std::endl;

        return true;

    }
       void file_to_read_xml(std::string ipath){
        path = ipath;
        read_xml_file();
        //draw_xml_file();
    }
    void file_to_read_xml(){
        read_xml_file();
    }

    std::vector<std::vector<int>> get_tileIDs(){
        return tileIDs;
    }
        
        bool read_xml_file(); //method to read the file.
        bool draw_xml_file();
        bool set_map_texture();
        bool make_tileset_file();
        bool draw_tileset_file(std::string name);
        bool draw_tileset_file(int pKey);
        bool is_int(const std::string& str);
        bool new_draw_tilemap();
        bool set_column();
        game_renderer_h_1::textureWrapper get_map_texture();
};
bool isInteger(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (const char& ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}
game_renderer_h_1::textureWrapper file_to_read::get_map_texture(){
    return mapTexture;
}
bool file_to_read::set_map_texture(){
   std::string name = path.substr(path.find_last_of("/\\") + 1); // Remove the path from the tileset name
    name = name.substr(0, name.find_last_of(".")); // also need to remove the .xml from the end of the name
    tileMapName = name;
   game_renderer_h_1::textureWrapper mapTexture1;
   mapTexture1.texture = LoadTexture(("Assets/" + name + ".png").c_str());
   std::cout << "HI" << std::endl;
   std:: cout << "Image path: " << "Assets/" + name << std::endl;
   mapTexture = mapTexture1;
   tileColumns = mapTexture1.texture.height / 16;
   std::cout << " we are out boiiiis" << std::endl;
   return true;
}
bool file_to_read::read_xml_file(){;
std::cout << "File path: " << path << std::endl;
    std::cout << "OUt" << std::endl;
    rapidxml::file<> xmlFile(path.c_str()); //Intilsise Class file
    if (xmlFile.data() == nullptr) {
    std::cerr << "Failed to open file: " << path << std::endl;
    return false;
}
    rapidxml::xml_document<> doc; 
    doc.parse<0>(xmlFile.data()); //Read from the file
  //  system("pause"); 
    rapidxml::xml_node<>* mapNode = doc.first_node("map"); //Create pointer to the first node/root node, which is the map node in all tilemaps created by Tiled.
    int tilemapWidth = std::stoi(mapNode->first_attribute("width")->value());  //Get the width of the tilemap 
    int tilemapHeight = std::stoi(mapNode->first_attribute("height")->value());//Get the height of the tilemap
    tileIDs = std::vector<std::vector<int>>(tilemapHeight, std::vector<int>(tilemapWidth)); //Create a vector of size the tile map's height and width.
    rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset"); //Get tileset node
   // system("pause");
  // std::cout<< "NOt rah " << std::endl;
    if (tilesetNode)
    {
       /* rapidxml::xml_node<>* secondNode = tilesetNode->first_node()->next_sibling(); // get the second child node
        if (secondNode)
        {
            std::cout << "Value of second node: " << secondNode->value() << std::endl; // print the value of the second node
        }
        */
      // std::cout << "rah" << std::endl;

    }
    else{
        return false;
    }
   // system("pause");
    int firstGID = std::atoi(tilesetNode->first_attribute("firstgid")->value()); //First Global ID
 //   std::cout << "after first gid" << std::endl;
  //  system("pause");
    tileSets.push_back(tilesetNode->first_attribute("source")->value()); //Get Tileset name
   // std::cout << "after push back" << std::endl;
   // system("pause");
   // std::cout<< "layernode and datanode";
    rapidxml::xml_node<>* layerNode = mapNode->first_node("layer"); //point to the Layer node
    rapidxml::xml_node<>* dataNode = layerNode->first_node("data"); // point to data node
  //  system("pause");
    if(dataNode == nullptr){ // return if the pointer is nulll
   //   std::cout << "No data node"<<std::endl; //For Debugging 
     return false; // Return if pointer is null
     }   
  //   std::cout<< "after datanode check" << std::endl;
  //   system("pause");
   // std::stringstream stringstream(dataNode->value()); //Create string stream to read from CSV (Comma Seperated Values) formatted tile IDs
   std::string stringstream1 = dataNode->value();
   std::stringstream stringstream(stringstream1);
    std::string temp; //Temporarily store ID while reading
    int current_row = 0; //Store current row in CSV we are reading from
   // std::cout << "after int current row" << std::endl;
    while(std::getline(stringstream, temp) && current_row < tilemapHeight){ //While the data is valid/ We are in the CSV data
        std::stringstream stringstreamcurrent_row(temp); 
        int current_column = 0;//Store current column in CSV we are reading from
        while(std::getline(stringstreamcurrent_row, temp, ',') && current_column < tilemapWidth){ //While the data is valid/ We are in the CSV data
      //  std::cout << "before std::stoi(temp)" << std::endl;
       // system("pause");
      //  std::cout << temp << std::endl;
        //system("pause");
       // if (isInteger(temp)) {
        try{
        tileIDs[current_row][current_column] = std::stoi(temp);
        std::cout << std::to_string(tileIDs[current_row][current_column]); 
        }
        catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << temp << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << temp << std::endl;
    }
        ++current_column;
    //}
     //    tileIDs[current_row][current_column] = std::stoi(temp) - firstGID; //Get the actual tileID from the tileset
        // std::cout << "after" << std::endl;
        // system("pause");
       //  ++current_column; //Increment column after reading from the whole column
         }
     ++current_row; //Increment row after reading from the whole row
    }
    return true; //Return true as we successfully (hopefully) read from the tilemap 
}
bool file_to_read::draw_xml_file(){
    if(tileIDs.size() <= 0){ 
        return false; //Return if the size of the vector of vectors is null.
    }
   // for(int i = 0; i < tileIDs.size(); i++){
   //     for(int j = 0; j < tileIDs[0].size();j++){
   //         std::cout << std::to_string(tileIDs[i][j]) << std::endl; 
   //     }
   // }
    return true;    
}

bool file_to_read::make_tileset_file(){
    if(tileSets.size() <= 0){
        std::cout<< " tilsets size is 0" << std::endl;
        return false;   
    }
    for(int i = 0; i < tileSets.size(); i++){ //For each tileset in the file    
    rapidxml::file<> xmlFile(("tilesets/" + tileSets[i]).c_str()); //Intilsise Class file
    rapidxml::xml_document<> doc; //Create a document
    doc.parse<0>(xmlFile.data()); //Read from the file
    rapidxml::xml_node<>* tilesetNode = doc.first_node("tileset"); //Get tileset node
    int tileWidth = std::stoi(tilesetNode->first_attribute("tilewidth")->value()); //Get tile width
    int tileHeight = std::stoi(tilesetNode->first_attribute("tileheight")->value()); //Get tile height
    int tileCount = std::stoi(tilesetNode->first_attribute("tilecount")->value()); //Get tile count
    
    int column = std::stoi(tilesetNode->first_attribute("columns")->value()); //Get columns
    tileColumns = column;
    tileset temp_tileset; //Create a tileset
    temp_tileset.name = tileSets[i]; //Set the name of the tileset
    temp_tileset.tileWidth = tileWidth; //Set the tile width
    temp_tileset.tileHeight = tileHeight; //Set the tile height
    temp_tileset.tileCount = tileCount; //Set the tile count
    rapidxml::xml_node<>* imageNode = tilesetNode->first_node("image"); //Get image node
    std::string imageSource = imageNode->first_attribute("source")->value(); //Get image source
    temp_tileset.image = imageSource; //Set image source
    temp_tileset.tileSetIDs.resize(temp_tileset.tileCount / temp_tileset.columns, std::vector<int>(temp_tileset.columns)); //Resize the vector of tileset IDs
    for(int i = 0; i < temp_tileset.tileSetIDs.size(); i++){ //For each row in the vector
        for(int j = 0; j < temp_tileset.tileSetIDs[0].size(); j++){ //For each column in the vector
            temp_tileset.tileSetIDs[i][j] = i * temp_tileset.columns + j; //Set the tileset ID
        }
    }
    // temp_tileset.tileSetIDs  
    
     imageWidth = std::stoi(imageNode->first_attribute("width")->value()); //Get image width
     imageHeight = std::stoi(imageNode->first_attribute("height")->value()); //Get image height
    temp_tileset.imageWidth = imageWidth; //Set image width
    temp_tileset.imageHeight = imageHeight; //Set image height
    tileset_vector.push_back(temp_tileset); //Push back the tileset
    }
    return true;
 }
 bool file_to_read::draw_tileset_file(std::string tileset_name){
    if(tileset_vector.size() <= 0){
        return false;   
    }
   int pKey = 0;
    for(int i = 0; i < tileset_vector.size(); i++){
        if(tileset_name == tileset_vector[i].name){
            pKey = i;
            break;
        }
        
    return true;
  }
 }
bool file_to_read::draw_tileset_file(int pKey){
    if(tileset_vector.size() <= 0){
        return false;   
    }

    // Load the tileset image
    Texture2D tilesetImage = LoadTexture(tileset_vector[pKey].image.c_str());
    std::cout << tileset_vector[pKey].image.c_str() << " IMAge" << std::endl;
   // std::cout << " NAH " << std::endl;
    // std::cout << tileset_vector[pKey].image.c_str() << std::endl;

    for(int j = 0; j < tileIDs.size(); j++){ // For each row in the tilemap
        for(int k = 0; k < tileIDs[0].size(); k++){
            // Calculate the source rectangle for the current tile
         //   std::cout <<  std::to_string(tileIDs[j][k]) + "current tile" << std::endl;
            int tileId = tileIDs[j][k];
            int tilesetRow = tileId % imageWidth;
            int tilesetColumn = tileId % tileset_vector[pKey].columns;
            Rectangle sourceRect = { tilesetColumn * tileset_vector[pKey].tileWidth, tilesetRow * tileset_vector[pKey].tileHeight, tileset_vector[pKey].tileWidth, tileset_vector[pKey].tileHeight };

            // Calculate the destination rectangle for the current tile
            Rectangle destRect = { k * tileset_vector[pKey].tileWidth, j * tileset_vector[pKey].tileHeight, tileset_vector[pKey].tileWidth, tileset_vector[pKey].tileHeight };

            // Draw the tile
            DrawTextureRec(tilesetImage, sourceRect, { destRect.x, destRect.y }, WHITE);

        }
    }

    // Unload the tileset image
    UnloadTexture(tilesetImage);

    return true;
}
bool file_to_read::set_column(){
     std::ifstream file("tilemaps.json");

    if (!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return false;
    
    }
    json json_file;
    file >> json_file;
    std::string tilemapName_J = tileMapName; 
if (json_file.find(tilemapName_J) != json_file.end()) {
        tileMapColumns = json_file[tilemapName_J];
        std::cout << "columns: from josn " << std::to_string(tileMapColumns) << std::endl;
        std::cout << "name of tilemap:json  " << tilemapName_J << std::endl;
    } 
    return true;
}
bool file_to_read::new_draw_tilemap(){
    int columns = 64;
    //N std::cout << "before crash" << std::endl;
    Rectangle sourceRect;
    Rectangle destRect;
    //N std::cout << "size of TileIds " << std::to_string(tileIDs.size()) << std::endl;
   //N std::cout << "size of TileIds[0] " << std::to_string(tileIDs[0].size()) << std::endl;
   


  //  std::cout << "tile column = " << std::to_string(tileColumns) << std::endl;
    for(int j = 0; j < tileIDs.size(); j++){ // tileIds.size() is the number of rows
        for(int k = 0; k < tileIDs[0].size(); k++){ // tileIds[0].size() is the number of columns
            // Calculate the source rectangle for the current tile
          //  std::cout <<  std::to_string(tileIDs[j][k]) + "current tile" << std::endl;
        //  std::cout << "columns = " << std::to_string(tileMapColumns) << std::endl;
            int tileId = tileIDs[j][k];
            int numTimes = tileId / tileMapColumns;
            int remainder = tileId % tileMapColumns;
        //    std::cout << "numtime for tile id: " << std::to_string(tileId) << " is " << std::to_string(numTimes) << std::endl;
      //      std::cout << "remainder for tile id: " << std::to_string(tileId) << " is " << std::to_string(remainder) << std::endl;
            Rectangle sourceRect = { (remainder * 16), (numTimes * 16), 16, 16 };
            //std::cout << "numTimes " << std::to_string(numTimes) << std::endl;
            // std::cout << "remainder " << std::to_string(remainder) << std::endl;
          //  std::cout << "sourceRect " << std::to_string(sourceRect.x) << std::endl;
            
            // Calculate the destination rectang+2le for the current tile
            Rectangle destRect = { k * 16, j * 16, 16, 16 };

            // Draw the tile.

            //DrawTextureRec(mapTexture.texture, sourceRect, { destRect.x, destRect.y }, WHITE);
            DrawTexturePro(mapTexture.texture, sourceRect, destRect, {0,0}, 0, WHITE);
            

        }
    }
    return true;
}
};


#endif
