#include <iostream>
#include <string>

int main()
{
    int peoplesoft_number;
    std::string full_name;

    std::cout << "Enter your PeopleSoft number: ";
    std::cin >> peoplesoft_number;

    std::cin.ignore(); // clear buffer for next input

    std::cout << "Enter your full name: ";
    std::getline(std::cin, full_name); // getline takes the entire line, independent of newlines

    std::cout << full_name << " has a netid of " << peoplesoft_number << std::endl;

    return 0;
}