#include "xml_parser.hpp"
#include <iostream>
#include <string>

int main(){
    std::string a_path = "testing_functionalilty_of_parser.xml";
    my_xml_parser::file_to_read x;
    x.file_to_read_xml(a_path);
    system("pause");
    return 1;
} 