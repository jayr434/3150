#include "check_utils.h"
namespace CheckUtils{
  int is_even(int n){
    if (n%2 == 0){
      return true;
    }
    return false;
  }
  int is_odd(int n){
    if (n%2 == 1) return true;
    return false;
  }
}

//c++ src/*.cpp -I include -std=c++23 -o program.out
