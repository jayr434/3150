#pragma once
#include <iostream>

class Point{
    double x_;  //[private_var]_;
    double y_;
public:
    Point() {x_ = y_ = 0;}  //default constructor, creates point (x,y) set to (0,0)
    Point(double x, double y): x_(x), y_(y) {}  //copy constructor: copies values from 
    Point(const Point& p):
        x_(p.getX()), y_(p.getY()) {}
    double getX() const {return x_;}
    double getY() const {return y_;}
    void set(double x, double y){x_ = x; y_ =y;}
    //Override copy assignment operator
    Point& operator = (const Point& p){
        x_ = p.x_;
        y_ = p.y_;
        return *this;
    }
    friend Point operator+(
        const Point& p1,
        const Point& p2
    ){
        return Point(
            p1.getX() + p2.getX(),
            p1.getY() + p2.getY()
        );
    }
    friend Point operator*(
        const Point& p1,
        double s
    ){
        return Point(
            p1.getX() * s,
            p1.getY() * s
        );
    }
    friend std::ostream& operator<<(
        std::ostream& os,
        const Point& p
    ){
        os << "(" << p.getX() << ", " << p.getY() << ")";
        return os;
    }
};