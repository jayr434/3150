#include <iostream>
int main() {
  char name[3] = {'J', 'a', 'y'};
  name[0] = 't';
  std::cout << name << std::endl;
  return 0;
}
