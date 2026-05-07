#include <iostream>

int main(){
    int age;
    std::cout << "Enter your age: "; // std::cout << "text"
    std::cin >> age;    // std::cin >> [var] 
    std::cout << "You entered " << age << std::endl;    // "text" << [var] << std::endl;
    
    int x, y;
    std::cin >> x >> y;
    std::cout << "x = " << x << "\ny = " << y << std::endl;

    return 0;
}

        
