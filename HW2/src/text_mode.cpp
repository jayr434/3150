#include "text_mode.h"
#include <iostream>
#include <string>
#include <cctype>

namespace text_mode {
    void run(int argc, char* argv[]) {
        if (argc < 3) {
            std::cout << "Usage: ./analyzer text <string>" << std::endl;
            return;
        }

        std::string str = argv[2];
        std::cout << "original str: " << str<<std::endl;

        std::size_t len = str.size();
        std::cout << "Len: " << len << std::endl;

        std::size_t letters = 0, digits = 0, spaces = 0, pun = 0;
        for (char c : str) {
            if (std::isalpha(static_cast<unsigned char>(c))) ++letters;
            if (std::isdigit(static_cast<unsigned char>(c))) ++digits;
            if (std::isspace(static_cast<unsigned char>(c))) ++spaces;
            if (std::ispunct(static_cast<unsigned char>(c))) ++pun;
        }

        std::cout << "letter: "<< letters << std::endl;
        std::cout << "digits: " << digits<< std::endl;
        std::cout << "spaces: " << spaces << std::endl;
        std::cout << "punctuations: " << pun<< std::endl;


        std::string upper = str;
        for (std::size_t i = 0; i < upper.size(); ++i) {
            upper[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(upper[i])));
        }
        std::cout << "uppercase str: " << upper << std::endl;

        for (std::size_t i = 0; i < str.size(); ++i) {
            str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        }
        std::cout << "lowercase str: " << str << std::endl;

        if (str.find("test") != std::string::npos) {
            std::cout << "Contains \"test\"" << std::endl;
        } else {
            std::cout << "Does not contain \"test\"" << std::endl;
        }

        std::size_t position = str.find(' ');
        if (position != std::string::npos) {
            std::string first = str.substr(0, position);
            std::cout << "First word: " << first << std::endl;
        }

    }
}
