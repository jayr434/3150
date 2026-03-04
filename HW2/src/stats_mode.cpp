#include "stats_mode.h"
#include <iostream>
#include <string>
#include <cctype>
#include <set>

namespace stats_mode {

    void run(int argc, char* argv[]) {
        if (argc < 3) {
            std::cout << "Usage: ./analyzer stats <string>" << std::endl;
            return;
        }

        std::string str = argv[2];
        std::size_t len = str.size();
        std::cout << "Len: " << len << std::endl;

        std::set<char> unique;
        for (char c : str) {
            unique.insert(c);
        }
        std::cout << "unique chars: " << unique.size() << std::endl;

        bool alnum = true;
        for (char c : str) {
            if (!std::isalnum(static_cast<unsigned char>(c))) {
                alnum = false;
                break;
            }
        }
        std::cout << "Only alphanumeric chars: " << (alnum ? "yes" : "no") << std::endl;

        std::string reversed = str;
        std::size_t left = 0;
        std::size_t right = reversed.size() - 1;
        while (left < right) {
            char temp = reversed[left];
            reversed[left] = reversed[right];
            reversed[right] = temp;
            ++left;
            --right;
        }
        std::cout << "reversed: " << reversed << std::endl;//print

        std::string remove_space;
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (str[i] != ' ') {
                remove_space += str[i];
            }
        }
        std::cout << "no spaces: " << remove_space << std::endl;

        std::string lower = remove_space;
        for (std::size_t i = 0; i < lower.size(); ++i) {
            lower[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(lower[i])));
        }

        bool palindrome = true;
        std::size_t l = 0;
        std::size_t r = lower.size() > 0 ? lower.size() - 1 : 0;
        while (l < r) {
            if (lower[l] != lower[r]) {
                palindrome = false;
                break;
            }
            ++l;
            --r;
        }
        std::cout << "Palindrome: " << (palindrome ? "yes" : "no") << std::endl;
    }

} // e
