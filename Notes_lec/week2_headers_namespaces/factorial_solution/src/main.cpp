#include <iostream>
#include "check_utils.h"
#include "math_extras.h"

int main() {
    int a = 5;
    int b = 6;

    if (CheckUtils::is_even(a)) {
        std::cout << a << " is even" << std::endl;
    } else {
        std::cout << a << " is odd" << std::endl;
    }

    if (CheckUtils::is_even(b)) {
        std::cout << b << " is even" << std::endl;
    } else {
        std::cout << b << " is odd" << std::endl;
    }

    std::cout << "factorial(" << a << ") = " << MathExtras::factorial(a) << std::endl;

    return 0;
}
