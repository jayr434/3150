#include <iostream>
#include "integer_utils.h"
#include "string_utils.h"
#include "grade_utils.h"
#include "while_count_utils.h"
#include "do_while_count_utils.h"

int main() {
    int choice;

    while (true) {
        std::cout << "1. Integer operations" << std::endl;
        std::cout << "2. Character arrays and C-style strings" << std::endl;
        std::cout << "3. Grade evaluation" << std::endl;
        std::cout << "4. While-loop counting" << std::endl;
        std::cout << "5. Do-while and range-based for counting" << std::endl;
        std::cout << "6. Quit" << std::endl;

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        switch (choice) {
            case 1:
                integer_utils::runIntegerOption();
                break;
            case 2:
                if (!string_utils::runStringOption()) return 1;
                break;
            case 3: {
                double grade = grade_utils::calculateGrade();
                if (grade < 0) return 1;
                break;
            }
            case 4:
                while_count_utils::runWhileCount();
                break;
            case 5:
                do_while_count_utils::runDoWhileCount();
                break;
            case 6:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            default:
                break;
        }
    }

    return 0;
}
