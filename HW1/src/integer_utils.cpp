#include <iostream>
#include "integer_utils.h" //quotes when using user defined headers

namespace integer_utils{
  void runIntegerOption(){  //enter first int, second int, 
    int a, b;
    std::cout << "Enter first integer";
    std::cin >> a;

    std::cout << "Enter second integer";
    std::cin >> b;

    if(b == 0){
      std::cout << "Error: division by zero";
      return;
    }

    std::cout << "Result: " << a / b << std::endl;

    //comment
    std::cout << "After post-increment: " << a++ << std::endl;
    std::cout << "After pre-increment: " << ++a << std::endl;
  }
}
