#include "add_mode.h"
#include <iostream>
#include <string>

#include <cctype>

namespace add_mode {
    int add(int a, int b) {
        return a + b;
    }
    double add(double a, double b) {
        return a + b;
    }
    std::string add(std::string a, std::string b) {
        return a + b;
    }

    static bool all(const std::string s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }

    void run(int argc, char* argv[]) {
        if (argc < 4) {
            std::cout << "Usage: ./analyzer add <valuea> <valueb>" << std::endl;
            return;
        }

        std::string a = argv[2];
        std::string b = argv[3];

        if (all(a) && all(b)) {
            int result = add(std::stoi(a), std::stoi(b));
            std::cout << "Result: " << std::to_string(result) << std::endl;
        }
        else if (a.find('.') != std::string::npos || b.find('.') != std::string::npos) {
            double result = add(std::stod(a), std::stod(b));
            std::cout << "Result: " << std::to_string(result) << std::endl;
        }
        else {
            std::string result = add(a, b);
            std::cout << "Result: " << result << std::endl;
        }
    }

} //p
