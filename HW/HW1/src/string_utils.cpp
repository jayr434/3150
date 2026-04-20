#include <iostream>
#include <string>
#include "string_utils.h"

namespace string_utils {
    bool runStringOption() {
        int length;

        std::cout << "Enter string length: ";
        std::cin >> length;

        if (length >= 20) {
            std::cout << "Error: length must be less than 20" << std::endl;
            return false;
        }

        std::cin.ignore();

        std::string input;
        std::cout << "Enter string: ";
        std::getline(std::cin, input);

        char arr[20];

        for (int i = 0; i < length; i++) {
            arr[i] = input[i];
        }

        arr[length] = '\0';

        std::cout << "C-style string: " << arr << std::endl;

        return true;
    }

}
