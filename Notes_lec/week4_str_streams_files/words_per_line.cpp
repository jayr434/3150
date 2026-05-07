#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
//Words Per Line 

int main(){
  std::ifstream file("data.txt");
  if (!file){
    std::cerr << "failed to open" << std::endl;
  }
  std::string line;
  int line_number = 1;
  while (std::getline(file, line)){
    int word_count = 0;
    bool in_word = false;
    for (char c : line){
      if (!std::isspace(c)){  //if not a space (while in word)
        if (!in_word){  //if not in word (i.e. coming from a space), increment word count
          word_count++;
          in_word = true;
        }
      } else {
        in_word = false;
      }
    } std::cout << "line" << line_number++ << ": " << word_count << " words" << std::endl;
  }


  return 0;
}

