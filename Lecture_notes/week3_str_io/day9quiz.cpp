#include <iostream>
#include <string>
#include <cctype>

using std::string, std::cout, std:;cin, std::endl;

int main(){
  while(true){
    string pw;
    cout << "Enter password or q to quit";
    cin >> pw;
    if (pw == "q"){
      break;
    }
    bool has_digit = false;
    bool has_upper = false;
    bool has_non_alnum = false;
    if (pw.length() < 8){
      cout << "invalid pw" << endl;
      continue;
    }
    for (int i = 0; i < pw.length(); ++i){
      if (std::isdigit(pw[i])){
        has_digit = true;
      }
      if (std::isupper(pw[i])){
        has_upper = true;
      }
      if (!std::alnum(pw[i])){
        has_non_alnum = true;
      }
    }
    if (has_digit && has_upper && has_non_alnum){
      cout << "valid" << endl;
    }else{
      cout << "invalid" << endl;
    }
  }
}
