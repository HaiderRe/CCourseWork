#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include "include/rapidxml.hpp"
#include "include/rapidxml_iterators.hpp"
#include "include/rapidxml_print.hpp"
#include "include/rapidxml_utils.hpp"
class file_to_read{
    std::string path; 
    int x = 2;
    std::vector<std::vector<int>> tileIDs;
    public:
       file_to_read(std::string input_path){
        path = input_path; 
       }
        void read_xml_file();
};

void file_to_read::read_xml_file(){
    // std::string w = "rararra";
    rapidxml::file<> xmlFile(path.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
}