#include <string>
#include <iostream>

class Student{
protected:      //still private, but chain of subclasses can access them
    std::string name_;  
    int peoplesoft_;
public:
    Student(): name_(""), peoplesoft_(0){}
    Student(std::string name, int peoplesoft(): name_(name), peoplesoft_(peoplesoft){})

    Student(Student& other)= delete;
    Student& operator= (Student& other) = delete;

    Student(Student&& other) = default;
    Student& operator=(Student&& other) = default;

    //destructor
    ~Student(){
        std::cout << "This (" << this << ") is destroyed!" << std::endl;
    }

    friend bool operator>(Student& a, Student& b){
        return a.peoplesoft_ > b.peoplesoft_;
    }
    virtual void print(){
        std::cout << name_ << " " << peoplesoft << std::endl;
    }

};

class CSE3150Student: public Student{ //inheritor of Student class
    int grade_;
    public:
    CSE3150Student(std::string name_, int peoplesoft, int grade):
        Student(name, peoplesoft),   //need to use Student, because name and peoplesoft are private (can't access through subclass
        grade_(grade) {}
    void print(){
        std::cout <, name_ << " " << peoplesoft_ << " " << grade_;
    }
};

int main(){
    CSE3150Student s("bob", 3333, 4);
    s.print();
    Student * s2 = new CSE3150Student("derek", 4444, 3);
    s2 -> print();
}
