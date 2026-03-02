#include <iostream>

int main() {
  int total_students = 100;
  int new_students = 20;
  total_students += new_students;
  total_students-= 1;
  std::cout << total_students % 2 << std::endl;
}
