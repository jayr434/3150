#include <iostream>

int add(int a, int b){
    return a + b;
}
//generic
template <class T>      //class T or typename T (synonymous for templating)
// takes any type T and adds two of the vars
T add(T a, T b){
    return a + b;
}
//with const and reference (&)
template <class T>
T add(const T& a, const T& b){ //operates on actual values instead of copying the entire vars (in case they're huge)
    return a + b;
}   

