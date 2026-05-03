#include <iostream>
#include <memory>

class Node{
public:
    int value;
    Node* next;
    Node(int v): value(v), next(nullptr) {}
};

int main(){
    //initialize
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    Node* current = head;
    while (current){
        std::cout << current->value << " ";
        current = current->next;
    }
    //free mem for each node
    current = head;
    while (current){
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    //must create a temporary node because we need to get the ->next value
    //if we delete current, then try current->next that's a "use after free" error

