#include <iostream>

// Function using pointers to access and modify original variables
void swapValues(int *ptr1, int *ptr2)
{
    // swap the VALUES, not the pointers themselves
    int temp = *ptr1;

    // Assign the value at address ptr2 to the address ptr1
    *ptr1 = *ptr2;

    // Assign the saved temp value to the address ptr2
    *ptr2 = temp;
}

int main()
{
    int num1, num2;

    std::cout << "Enter two integers: ";
    std::cin >> num1 >> num2;
    std::cout << "Before swap: " << num1 << " " << num2 << std::endl;

    // pass by reference
    swapValues(&num1, &num2);

    std::cout << "After swap: " << num1 << " " << num2 << std::endl;

    return 0;
}