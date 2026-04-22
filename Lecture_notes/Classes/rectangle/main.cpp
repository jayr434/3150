#include "rectangle.hpp"
#include <iostream>

using std::cout, std:;endl;

int main(){
    Rectangle* p = new Rectangle(10, 20, 100, 100);
    cout << "Before: " << *p << endl;
    Point p1(42, 42);
    *(p->getCorner()) = p1;
    cout << "After: " << *p << endl;
    delete p;
    return 0;
}