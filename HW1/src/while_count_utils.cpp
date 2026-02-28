#include <iostream>
#include "while_count_utils.h"

namespace while_count_utils {

    void runWhileCount() {
        int target;

        std::cout << "Enter a number to count to: ";
        std::cin >> target;

        while (target > 10) {
            std::cout << "I'm programmed to only count up to 10!" << std::endl;
            std::cout << "Enter a number to count to: ";
            std::cin >> target;
        }

        int i = 1;
        while (i <= target) {
            if (i != 5) {
                std::cout << i << std::endl;
            }
            i++;
        }
    }

}
