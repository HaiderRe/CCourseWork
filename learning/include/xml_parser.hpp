#include <iostream>
#include <string> 
#include <vector>
#include <sstream>
#include "rapidxml.hpp"
// #include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
namespace my_xml_parser{
class file_to_read{
    private:
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<std::string> tileSets;
    public:
    file_to_read(){
    std::string path; //create a string to hold the path
    std::vector<std::vector<int>> tileIDs; // Vector of a vector of ints containing the tileIDs of a tilemap.
    std::vector<std::string> tileSets;
    } 
       void file_to_read_xml(std::string ipath){
        path = ipath;
        read_xml_file();
        draw_xml_file();
    }
        bool read_xml_file(); //method to read the file.
        bool draw_xml_file();
        bool make_tileset_file();
};

bool file_to_read::read_xml_file(){
    rapidxml::file<> xmlFile(path.c_str()); //Intilsise Class file
    rapidxml::xml_document<> doc; 
    doc.parse<0>(xmlFile.data()); //Read from the file 
    rapidxml::xml_node<>* mapNode = doc.first_node("map"); //Create pointer to the first node/root node, which is the map node in all tilemaps created by Tiled.
    int tilemapWidth = std::stoi(mapNode->first_attribute("width")->value());  //Get the width of the tilemap 
    int tilemapHeight = std::stoi(mapNode->first_attribute("height")->value());//Get the height of the tilemap
    tileIDs = std::vector<std::vector<int>>(tilemapHeight, std::vector<int>(tilemapWidth)); //Create a vector of size the tile map's height and width.
    rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset"); //Get tileset node
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
    int firstGID = std::stoi(tilesetNode->first_attribute("firstgid")->value()); //First Global ID
    tileSets.push_back(tilesetNode->first_attribute("source")->value()); //Get Tileset name
    rapidxml::xml_node<>* layerNode = mapNode->first_node("layer"); //point to the Layer node
    rapidxml::xml_node<>* dataNode = layerNode->first_node("data"); // point to data node
    if(dataNode == nullptr){ // return if the pointer is nulll
        std::cout << "No data node"<<std::endl; //For Debugging 
     return false; // Return if pointer is null
     }   
    std::istringstream stringstream(dataNode->value()); //Create string stream to read from CSV (Comma Seperated Values) formatted tile IDs
    std::string temp; //Temporarily store ID while reading
    int current_row = 0; //Store current row in CSV we are reading from
    while(std::getline(stringstream, temp, '\n') && current_row < tilemapHeight){ //While the data is valid/ We are in the CSV data
        std::istringstream stringstreamcurrent_row(temp); 
        int current_column = 0;//Store current column in CSV we are reading from
        while(std::getline(stringstreamcurrent_row, temp, ',') && current_column < tilemapWidth){ //While the data is valid/ We are in the CSV data
         tileIDs[current_row][current_column] = std::stoi(temp) - firstGID; //Get the actual tileID from the tileset
         ++current_column; //Increment column after reading from the whole column
         }
     ++current_row; //Increment row after reading from the whole row
    }
    return true; //Return true as we successfully (hopefully) read from the tilemap 
}
bool file_to_read::draw_xml_file(){
    if(tileIDs.size() <= 0){ 
        return false; //Return if the size of the vector of vectors is null.
    }
    for(int i = 0; i < tileIDs.size(); i++){
        for(int j = 0; j < tileIDs[0].size();j++){
            std::cout << tileIDs[i][j] << std::endl; 
        }
    } 
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