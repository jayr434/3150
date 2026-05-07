#include <iostream>
#include <string>

using std::cout, std::cin, std::endl, std::string;

int main(){
    int x = 5;
    //const int* px = &x;     //Read right to left: pointer to an int, that is constant
    int* const px =&x;      // pointer, that is constant, to an int 
                            // The address cannot be changed (ptr always points to same var), but value can be changed 
    int y = 7;
    int px =&y 
    px* = 10;    
    cout << "px=" << px << endl;    //print address stored at ptr
    cout<< "*px=" << *px << endl;   // print value stored at address stored at ptr
    //*px = 50;
    return 0;
}
/* so const ___ ptr px just means you cannot modify the value at the address stored by px 
 * through the pointer px */ 

