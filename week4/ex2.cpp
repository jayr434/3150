#include <sstream>
#include <string>
#include <iostream>
//String Streams 

int main(){
  std::string line = "10 20 30";  //same as inputting stream std::cin "..."
  std::istringstream iss(line); //convert string line into stream 
  int a, b, c;
  iss >> a >> b >> c;
  std::cout << a + b + c << std::endl;
  return 0;
}
