#include <iostream>
#include <memory>

class Node{
public:
    int value;
    std::shared_ptr<Node> next;
    Node(int v): value(v), next(nullptr) {}
};

int main(){
    //initialize
    auto head = std::make_shared<Node>(1);
    head->next = std::make_shared<Node>(2);
    head->next->next = std::make_shared<Node>(3);
    //print(iterate)
    auto current = head;
    while (current){
        std::cout << current->value << " ";
        current = current->next;
    }
    //with unique ptr, it automatically cleans it up for us.
