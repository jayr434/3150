#include <vector>
#include <iostream>
//summing up Vector
int sum_vector(std::vector<int> v){
    int sum = 0;
    for (int x : v){
        sum += x;
    }
    return sum;
}

template<class T, class InputIter>  //InputIter is the type of the container (vector, or linked list, etc) 
T sum(InputIter start, InputIter end, T total){
    T total{};
    for(; start != end; start++){
        total += *start;
    }
    return total;
}
//helper function
template<class T, class Container>
T call_sum(Container container, T total){
    return sum(start: container.begin(), container.end(), total);
}

int main(){
    std::vector<int> v = {[0]=1, [1]=2, [2]=3, [3]=4};
    int total = call_sum(v, 0);
    //int total = call_sum(start: v.begin(), end: v.end(), total: 0);
    std::cout << total << std::endl;
    return 0;
}
