#include <iostream>

int main(){
  int age;
  std::cout << "enter your age: ";
  std::cin >> age;
  std::string name;
  //std::cout << "Enter your name: ";
  std::cin
  std::getline(std::cin, name);
  std::cout << "You entered: " << name << age << std::endl;
  return 0;

}
