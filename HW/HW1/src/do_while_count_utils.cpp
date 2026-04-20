#include <iostream>
#include "do_while_count_utils.h"

namespace do_while_count_utils {

    void runDoWhileCount() {
        int input;

        do {
            std::cout << "Enter a number between 1 and 5: ";
            std::cin >> input;
        } while (input < 1 || input > 5);

        int arr[] = {1, 2, 3, 4, 5};

        for (int val : arr) {
            std::cout << "Value: " << val << std::endl;
            if (val == input) {
                break;
            }
        }
    }

}
