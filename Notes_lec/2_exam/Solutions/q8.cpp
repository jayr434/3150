#include <iostream>

void swapValues(int &a, int &b) // create alias for original objects (do not copy)
{
    int temp = a; // temp does not need to be by reference bc it is only used inside this function.
    a = b;
    b = temp;
}

int main()
{
    int num1, num2;

    std::cout << "Enter two integers: ";
    std::cin >> num1 >> num2;

    std::cout << "Before swap: " << num1 << " " << num2 << std::endl;

    swapValues(num1, num2);

    std::cout << "After swap: " << num1 << " " << num2 << std::endl;

    return 0;
}