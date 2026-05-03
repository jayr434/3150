#include <iostream>
#include <memory>

int main(){
    int x = 1;
    int* y = new int(1);
    auto up = std::make_unique<int>(1);
    auto sp = std::make_shared<int>(1);
    auto sp_copy = sp;
    std::weak_ptr<int> wp(sp);   //make shared ptr first
    delete y; //y is raw ptr, prevent memory leak
}


