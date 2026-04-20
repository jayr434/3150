#include <sstream>
#include <string>

int main(){
  std::string line = "C++ language";
  std::isstringstream iss(line);
  std::string word;
  int count = 0;
  while (iss >> word) {
    count++;
  }
  std::cout << count << std::endl;
  return 0;
}
