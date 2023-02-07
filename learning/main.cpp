#include <iostream> 
#include <string>
int main(){
    int rah;
    std::string hey;
    while(1){
    unsigned int haider = 40;
    int bob = haider *2; 
    std::cout << bob << std::endl; 
    std::cout << "Test" << std::endl;
    std::getline(std::cin, hey);
    std::cin >> rah; 
    if( rah == 3){
        break;
    }
    system("pause");
   } 
   std::cout << hey + " rah" << std::endl;
   system("pause");
     return 0;
}