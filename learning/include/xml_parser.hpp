#ifndef xml_parser
#define xml_parser
#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include <windows.h>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "raylib.h"
namespace my_xml_parser{
<<<<<<< HEAD
<<<<<<< HEAD
class tileset{
    public:
    std::string name;
    int firstGID;
    Texture2D texture; // store texture
    tileset(std::string path, std::string imgPath) {
        std::string name = path; 
        texture = LoadTexture(imgPath.c_str()); // load texture
    }
};
=======
>>>>>>> parent of 5077214 (Fixed xml_parser)
=======
>>>>>>> parent of 5077214 (Fixed xml_parser)
class file_to_read{
    private:
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
<<<<<<< HEAD
<<<<<<< HEAD
    std::vector<tileset> tileSets;
    
=======
    std::vector<std::string> tileSets;
>>>>>>> parent of 5077214 (Fixed xml_parser)
    public:
    file_to_read(){
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<tileset> tileSets;
=======
    std::vector<std::string> tileSets;
    public:
    file_to_read(){
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<std::string> tileSets;
>>>>>>> parent of 5077214 (Fixed xml_parser)
    } 
       void file_to_read_xml(std::string ipath){
        path = ipath;
        read_xml_file();
        //draw_xml_file();
    }
        bool read_xml_file(); //method to read the file.
        void draw_xml_file(std::string xmlFile);
        bool make_tileset_file();
        bool is_int(const std::string& str);
        const std::vector<tileset>& getTileSets() const {
        return tileSets;
    }   

    // Given a tile ID, returns the appropriate texture
    const Texture2D& getTextureForTileID(int tileID) const {
        // Logic to map tileID to the appropriate tileset
        // This highly depends on how your tileID is structured
        // As an example, if tileID corresponds to index in tileSets
        if(tileID >= 0 && tileID < tileSets.size()) {
            return tileSets[tileID].texture;
        }

        // If no matching tileID is found, throw an error or return a default texture
        throw std::runtime_error("TileID does not correspond to any tileset");
    }
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
bool file_to_read::read_xml_file(){;
    rapidxml::file<> xmlFile(path.c_str()); //Intilsise Class file
    rapidxml::xml_document<> doc; 
    doc.parse<0>(xmlFile.data()); //Read from the file
  //  system("pause"); 
    rapidxml::xml_node<>* mapNode = doc.first_node("map"); //Create pointer to the first node/root node, which is the map node in all tilemaps created by Tiled.
    int tilemapWidth = std::stoi(mapNode->first_attribute("width")->value());  //Get the width of the tilemap 
    int tilemapHeight = std::stoi(mapNode->first_attribute("height")->value());//Get the height of the tilemap
    tileIDs = std::vector<std::vector<int>>(tilemapHeight, std::vector<int>(tilemapWidth)); //Create a vector of size the tile map's height and width.
    rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset"); //Get tileset node
   // system("pause");
    if (tilesetNode)
    {
       /* rapidxml::xml_node<>* secondNode = tilesetNode->first_node()->next_sibling(); // get the second child node
        if (secondNode)
        {
            std::cout << "Value of second node: " << secondNode->value() << std::endl; // print the value of the second node
        }
        */
       std::cout << "rah" << std::endl;
    }
    else{
        return false;
    }
   // system("pause");
    int firstGID = std::atoi(tilesetNode->first_attribute("firstgid")->value()); //First Global ID
    std::cout << "after first gid" << std::endl;
  //  system("pause");
    tileSets.push_back(tilesetNode->first_attribute("source")->value()); //Get Tileset name
    std::cout << "after push back" << std::endl;
   // system("pause");
   // std::cout<< "layernode and datanode";
    rapidxml::xml_node<>* layerNode = mapNode->first_node("layer"); //point to the Layer node
    rapidxml::xml_node<>* dataNode = layerNode->first_node("data"); // point to data node
  //  system("pause");
    if(dataNode == nullptr){ // return if the pointer is nulll
        std::cout << "No data node"<<std::endl; //For Debugging 
     return false; // Return if pointer is null
     }   
  //   std::cout<< "after datanode check" << std::endl;
  //   system("pause");
    std::istringstream stringstream(dataNode->value()); //Create string stream to read from CSV (Comma Seperated Values) formatted tile IDs
    std::string temp; //Temporarily store ID while reading
    int current_row = 0; //Store current row in CSV we are reading from
   // std::cout << "after int current row" << std::endl;
    while(std::getline(stringstream, temp, '\n') && current_row < tilemapHeight){ //While the data is valid/ We are in the CSV data
        std::istringstream stringstreamcurrent_row(temp); 
        int current_column = 0;//Store current column in CSV we are reading from
        while(std::getline(stringstreamcurrent_row, temp, ',') && current_column < tilemapWidth){ //While the data is valid/ We are in the CSV data
      //  std::cout << "before std::stoi(temp)" << std::endl;
       // system("pause");
      //  std::cout << temp << std::endl;
        //system("pause");
       // if (isInteger(temp)) {
        tileIDs[current_row][current_column] = std::stoi(temp);
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
void file_to_read::draw_xml_file(std::string xmlFile) {
    std::ifstream file(xmlFile);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
  
    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    // Find the map node
    rapidxml::xml_node<> *mapnode = doc.first_node("map");

    // Get map attributes
    int mapWidth = std::stoi(mapnode->first_attribute("width")->value());
    int mapHeight = std::stoi(mapnode->first_attribute("height")->value());
    int tileWidth = std::stoi(mapnode->first_attribute("tilewidth")->value());
    int tileHeight = std::stoi(mapnode->first_attribute("tileheight")->value());

    tilemap tileMap; 
    tileMap.set_width_height_of_arr(mapWidth, mapHeight);
    tileMap.set_width_height(tileWidth, tileHeight);

    // Find the layer node
    rapidxml::xml_node<> *layernode = mapnode->first_node("layer");

    // Find the data node
    rapidxml::xml_node<> *datanode = layernode->first_node("data");

    // Read the data content (csv format)
    std::string data = datanode->value();
    std::stringstream ss(data);
    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            std::string val;
            std::getline(ss, val, ',');
            int gid = std::stoi(val);
            tileMap.set_tile(x, y, gid);
        }
    }
    // then you can draw your tilemap
    tileMap.draw();
}
bool file_to_read::make_tileset_file(){
    if(tileSets.size() <= 0){
        return false;   
    }
    for(int i = 0; i < tileSets.size(); i++){ //For each tileset in the file    
    rapidxml::file<> xmlFile(("tilesets/" + tileSets[i]).c_str()); //Intilsise Class file
    rapidxml::xml_document<> doc; 
    doc.parse<0>(xmlFile.data()); //Read from the file
    } 
 }
}



#endif // xml_parser
