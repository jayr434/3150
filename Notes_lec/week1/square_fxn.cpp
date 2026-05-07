#include <iostream>

int square(int x){
  return x * x;
}

int main(){
  int z = 8;
  int s = square(z);
  std::cout << s << std::endl;
  return 0;
}
