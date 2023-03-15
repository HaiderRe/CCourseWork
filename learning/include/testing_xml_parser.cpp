#include "xml_parser.hpp"
#include <iostream>
#include <string>

int main(){
    std::string a_path = "testing_functionalilty_of_parser.xml";
    my_xml_parser::file_to_read x;
    x.file_to_read_xml(a_path);
    x.draw_xml_file();
    system("pause");
    std::string y;
    while(1) {
    std::cin >> y;
    if(y == "b"){
        break;
    }
    } 
    return 1;
} 