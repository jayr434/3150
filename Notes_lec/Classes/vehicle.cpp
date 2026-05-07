#include <iostream>

using std::cout, std::endl;

class Vehicle {
public:
    Vehicle() {}
    void print() const{
        cout << "I(" << this << ")'m a vehicle" << endl;
    }
};
class Car : public Vehicle {
public:
    Car() {}
    void print(){
        cout << "I(" << this << ")'m a car" << endl;
    }
};

void foo(const Vehicle& v){
    v.print();
}

int main() {
    Vehicle v;
    Car v;
    v.print();
    c.print();
    foo(v);
    foo(c);
    return 0;


