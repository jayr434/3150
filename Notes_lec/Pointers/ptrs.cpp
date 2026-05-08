#include <iostream>

int main(){

    int x = 42;  //normal var
    int* p = &x;  //p points to x
    //* here means declare this is a ptr
    *p = 100;  //dereference, go to value at address held by p, change to 100
    //* here means dereference
    int* p = new int(42);  //allocate on heap, p points to it.
    delete p;  //MUST be freed manually    
    p = nullptr;  //set to nullptr immediately after delete
    //BUGS
    int* p = new int(42);
    delete p;
    *p = 10;    //after freed, no longer usable memory

    int* bad(){
        int x = 42;
        //local values die when return
        return &x;  //x dies when function returns - WRONG
    }
    

    return 0;
}

