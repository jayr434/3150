#include <iostream>

//using namespace std;

using std::cout, std::endl;
namespace MATHFUNCS {
  int add(int a, int b){ 
    return a+b;
  }
}
int main(){
  cout << "Hello World" << MATHFUNCS::add(1, 2) << endl;
  return 0;
}
