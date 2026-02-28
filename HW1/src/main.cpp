#include <iostream>

#include "integer_utils.h"

void menu(){
  std::cout
    << "\n 1. Integer operations\n"
    << "2. Character arrays and C-style strings\n"
    << "3. Grade evaluation\n"
    << "4. While-loop counting\n"
    << "5. Do-while and range-based for counting\n"
    << "6. Quit\n";
}

int main(){
  while (true){
    menu();
  }

  int choice;
  if (!(std::cin >> choice)){
    std::count << "Enter a number option 1-6\n";
    std::cin.clear();
    std::cin.ignore();
  }



  return 0;
}
