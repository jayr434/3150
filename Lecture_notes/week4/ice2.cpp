#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>

using std::cout, std::cin, std::endl, std::cerr, std::string;

int main(){
  int count;
  cout << "How many entries?";
  cin.ignore();
  cin >> count;
  std::ofstream file("entries.txt");
  if (!file){
    cerr << "Failed to open" << endl;
    return 1;
  }
  for (int i = 0; i <= count; i++){
    string line;
    cout << "Enter text: ";
    std::getline(cin, line);
    file << line << endl;
  }
  return 0;
}
/*
int main(){
  int loops;
  std::string input;
  std::cin >> loops <<

}
*/
