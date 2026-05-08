#include <iostream>
#include <memory>   //for smart pointers
//smart pointers automatically call delete when they go out of scope

//unique_ptr
std::unique_ptr<int> p = std::make_unique<int>(42);
std::cout << *p <<std::endl;


int main(){
    return 0;
}