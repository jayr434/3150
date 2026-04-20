#include <iostream>
#include <string>

using std::cout, std::cin, std::endl, std::string;

int main(){
    int x = 5;
    int y = 7;
    const int* px = &x;     //setting *value that px is point to* as constant
                            //So we cannot change what's in the pointer's memory block THROUGH THE PTR 
                            //we can still change the value through x, since x is not a constant variable
    x = 10;    
    cout << "px=" << px << endl;    //print address stored at ptr
    cout<< "*px=" << *px << endl;   // print value stored at address stored at ptr
    *px = 50;
    return 0;
}
/* so const ___ ptr px just means you cannot modify the value at the address stored by px 
 * through the pointer px */ 

