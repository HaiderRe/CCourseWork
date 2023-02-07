#include <iostream>
using namespace std;

int main(){
    string name;
cout << "Give me your name and surname:"<<endl;
cin >> name;
int age;
cout << "Give me your age:" <<endl;
cin >> age;
cout << cin.rdstate() << endl; 
cin.clear(); //new line is here :-)
cout << cin.rdstate()<< endl;  //new line is here :-)
system("Pause");
return 0;
}