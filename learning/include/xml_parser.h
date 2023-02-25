#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
class file_to_read{
    std::string path;
    int width; 
    int height; 
    bool read;
    std::string *tilesets;
    public: 
     void read_file();
};