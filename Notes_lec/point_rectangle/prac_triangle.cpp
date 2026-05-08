#include <iostream>
#include <memory>
#include <ostream>
#include "point.hpp"

class Triangle{
   Point* corner_;
   Point* top_;
   double area_; 
public:
    Triangle(): corner_(Point()), top_(Point()), area_(0) {}
    Triangle()
}
/*
`class(): var1_(val()), var2_(init_val), var3_(init_val)) {}`
- class(): [member initializer list]
    - member_name(initializing_value)
    - var1_(val())
        - val(): calling val's default constructor

*/
