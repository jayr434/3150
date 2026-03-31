#include <iostream>
#include <string>

using std::cout, std::cin, std::endl, std::string;

int main(){
    string s = "Hello";
    for (const char& c : s){ //iterate through 
        c = 'a';
        cout << c << endl;
    }
    return 0
}


