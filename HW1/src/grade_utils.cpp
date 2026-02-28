#include <iostream>
#include "grade_utils.h"

namespace grade_utils {
    double calculateGrade() {
        char studentType;
        double grade;

        std::cout << "Enter student type (U for undergrad, G for grad): ";
        std::cin >> studentType;

        std::cout << "Enter numeric grade: ";
        std::cin >> grade;

        if (grade < 0 || grade > 100) {
            std::cout << "Invalid grade" << std::endl;
            return -1;
        }

        bool pass = false;
        if (studentType == 'U' || studentType == 'u') {
            pass = grade >= 60;
        } else {
            pass = grade >= 70;
        }

        if (pass) {
            std::cout << "Status: Pass" << std::endl;
        } else {
            std::cout << "Status: Fail" << std::endl;
        }

        return grade;
    }

}
