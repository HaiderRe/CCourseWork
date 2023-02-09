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
cin.clear();
cin.ignore(10000, '\n'); //ignore after clear
cout << cin.rdstate() << endl;
while(!(cin >> age)){
    cin.clear();
    cin.ignore(10000, '\n');
}//new line is here :-)
cout << age << endl;
//cout << age << endl;
system("Pause");
return 0;
}