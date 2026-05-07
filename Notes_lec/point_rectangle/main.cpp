#include "point.hpp"
#include <iostream>

using std::cout, std::endl;

int main(){
    Point a(1.0, 2.0);
    Point b(3.0, 4.0);
    Point c = a + b;
    Point d = c * 2.0;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;
    return 0;
}