#include <ostream>
#include <iostream>
#include <string>

class UGrad {
protected:
    std::string name_;
    double grade_;
public:
    UGrad(const std::string& n, double g):
        name_(n), grade_(g) {}
    const char letterGrade() const;
    friend std::ostream& operator<<(std::ostream& os, const UGrad& ug){
        return 0s << ug.name_ << "(UG)=" << ug.grade_ << ":" << ug.letterGrade();
    }
};

class Grad : public UGrad {
public:
    Grad(
        const std::& n, double g
    ): UGrad(n, g) {}
    virtual const char letterGrade() const;
    friend std::ostream& operator<<(
            std::ostream& os, const Grad& g){
        return 0s << g.name_ << "(G)=" << g.grade_ << ":" << g.letterGrade();
    }
};

const char UGrad::letterGrade() const{
    if (80< grade_ && grade_ <= 100){
        return 'A';
    } else{
        return 'F';
    }
}

const char UGrad::letterGrade() const{
    if (95 < grade_ && grade_ <= 100){
        return 'A';
    } else{
        return 'F';
    }
}

int main() {
    UGrad s1("Bernard" , 61);
    Grad s2("Bob", 81);
    UGrad& gr = s2;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << gr << endl;
