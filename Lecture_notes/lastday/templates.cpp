#include <iostream>
#include <memory>
#include <concepts>

template<typename T>
concept Comparable = 
    requires(T a, T b){
        {a > b} -> std::convertible_to<bool>;
    };
//two params, return larger value

template<Comparable T> //template
T max(T a, T b){return a > b ? a : b;}

int main(){}
