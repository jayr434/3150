#include <iostream>

void print_number(int x){ //pass by value
  std::cout << "!" << x << "!" <<std::endl;
}

int main(){
  int num = 42;
  print_number(num);
  std::cout << num << std::endl;
  return 0;
}
