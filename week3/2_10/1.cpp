#include <iostream>

int add(int a, int b){
  return a + b;
}

double add(int a, int b, int c){
  return a + b + c;
}

int main(){
  std::cout << add(1, 2) << std::endl;
  std::cout << add(1, 2, 3) << std::endl;
  return 0;
}


