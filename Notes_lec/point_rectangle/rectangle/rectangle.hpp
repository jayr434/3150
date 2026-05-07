#include <memory>
#include <ostream>
#include "point.hpp"

class Rectangle {
    Point* corner_;  //corner_(Point()): initialize corner_ with Point's default constructor, Point()    
    double w_, h_;     
public:
    Rectangle(): corner_(new Point()), w_(0), h_(0) {}  
    Rectangle( double x, double y, double w, double h):  //copy constructor
        corner_(new Point(x, y)), w_(w), h_(h) {}  //corner declared as a pointer to a Point
    Point getCorner() const {return corner_;} 
    double getWidth() const {return w_;}
    double getHeight() const {return h_;}
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& r){
        return os << "rect(" << *r.corner_ << ", " << r.w_ << ", " << r.h_ << ")";
    }
};