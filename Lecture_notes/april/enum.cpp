#include <iostream>
#include <string>

using std::cout, std::endl;

enum class Status { //scoped enums
    PENDING,
    APPROVED,
    REJECTED
};

int main(){
    Status s = Status::APPROVED;
    if (s== Status::APPROVED){
        cout << "Approved!" << endl;
    }
    int s = 0;
    if (s==1)
        cout << "Approved!" << endl;
    return 0;
}
