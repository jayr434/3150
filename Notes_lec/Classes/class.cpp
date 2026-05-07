#include <string> 
#include <iostream>
#include <cctype>

using std::cout, std::endl;

class Rectangle { 
//private:
    double width_;  //underscore conventionally means private vars
public:
    Rectangle(double width, double height){     //function included in class definition
        width_ = width;
        height_ = height;
    }
    //Rectangle(double w, double h): width_(w), height_(h) {} // constructor (more efficient)
    double height_;
    double area() const; //inside area() fxn, rectangle instance will NOT be modified (compiler-enforced)
    void setWidth(double width);
    double getWidth() const;
};

double Rectangle::area() {
    return width_ * height_;
}

void Rectangle::setWidth(double width){     //since width is private, can't do r.width = ..., so use fxn 
    width_ = width;
}

double getWidth(){
    return width_;
}

int main(){
    Rectangle r(5, 2);
    //r.setWidth(5);
    //r.height_ = 2;
    cout <<r.getWidth() << endl;
    return 0;
}

//--initialize struct
//Rectangle n; //n : name of instance 
//n.func1(param);   
//n.var1 = 10;

