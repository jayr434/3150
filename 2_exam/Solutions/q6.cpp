#include <iostream>

int main()
{
    int *px = new int[5]; // allocate memory

    // assign values
    for (int *cx = px; cx < px + 5; cx++)
    {
        *cx = static_cast<int>(cx - px); // assign each block to its 'index'
    }

    // print values
    for (int *cx = px; cx < px + 5; cx++)
    {
        std::cout << "Value at " << cx << " is " << *cx << std::endl;
    }

    delete[] px; // free allocated memory

    return 0;
}