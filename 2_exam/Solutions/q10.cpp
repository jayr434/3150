#include <iostream>

// Function that creates a heap-allocated copy of values from a pointer array
// Pattern: Takes a Stack Array of Heap Values and returns a Heap Array
int *foo(int *stackArr[5], int size) // function that "moves" a stack-array of pointers to heap values, to an entirely heap-allocated array.
{
    int *heapArray = new int[size];

    for (int i = 0; i < size; i++)
    {
        // Copy the VALUE (dereference the pointer) into the new array
        heapArray[i] = *(stackArr[i]);
    }

    return heapArray; // Return the pointer to the heap-allocated array
    // this is okay because the value pointed to is not within this function, but on the heap!!
}

int main()
{
    const int SIZE = 5;

    int *pointerArray[SIZE]; // declare an array of size 5 on the stack storing pointers to integers

    for (int i = 0; i < SIZE; i++) // populate the array with integers on the heap (with pointers)
    {
        pointerArray[i] = new int(i * 10);
    }

    int *resultArr = foo(pointerArray, SIZE); // get new heap array

    // print values
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << "Address: " << &resultArr[i]
                  << " | Value: " << resultArr[i] << std::endl;
    }

    // free heap-allocated memory from main
    for (int i = 0; i < SIZE; i++)
    {
        delete pointerArray[i];
    }

    // free the array we allocated from inside foo
    delete[] resultArr;

    return 0;
}