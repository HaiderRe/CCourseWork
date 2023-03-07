#include <iostream> 
#include <string>
int main(){
    std::string size_of_a;
    std::cout << "How big of an array do you want?:";
    std::cin >> size_of_a;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    int* foo;
    
    foo = new int[std::stoi(size_of_a)];
    for(int i = 0; i < std::stoi(size_of_a); i++){
        std::cout << "Enter a Number to enter into the arr:";
        std::cin >> foo[i];
    }
    for(int i = 0; i < std::stoi(size_of_a); i++){
        std::cout << std::to_string(foo[i]) << std::endl;
    }
    delete[] foo;
    system("Pause");
    return 0;
}