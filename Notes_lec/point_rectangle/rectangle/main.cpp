#include "rectangle.hpp"
#include <iostream>

using std::cout, std::endl;

int main(){
    Rectangle* p = new Rectangle(10, 20, 100, 100); //pointer to rectangle object
    cout << "Before: " << *p << endl;
    Point p1(42, 42);
    *(p->getCorner()) = p1; //dereference getCorner()'s return value and assign through it

    cout << "After: " << *p << endl;
    delete p;
    return 0;
}