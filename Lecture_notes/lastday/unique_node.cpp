#include <iostream>
#include <memory>

class Node{
public:
    int value;
    std::unique_ptr<Node> next;
    Node(int v): value(v), next(nullptr) {}
};

int main(){
    //initialize
    auto head = std::make_unique<Node>(1);
    head->next = std::make_unique<Node>(2);
    head->next->next = std::make_unique<Node>(3);
    //print(iterate)
    Node* current = head.get();
    while (current){
        std::cout << current->value << " ";
        current = current->next.get();
    }
    //with unique ptr, it automatically cleans it up for us.
