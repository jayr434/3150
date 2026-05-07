#include "include/text_mode.h"
#include <iostream>
#include <string>

#include <cctype>   //std::isXYZ functions

namespace text_mode{    //namespace matching header file
    void run(int argc, char *argv[]){   //test correct inputs/usage
        if (argc < 3){
            std::cout << "Usage: ./analyzer <mode> <string>" << std::endl;
            return;
        }
        
        std::string str = argv[2];  //cpp string set to <mode> value
        std::cout << "Original string: " << str << std::endl;

        std::size_t strlen = str.size();
        std::cout << "String length: " << strlen << std::endl;

        std::size_t letters = 0, digits = 0, spaces = 0, punct = 0;
        for (char c : str) { //iterate by char on string
            if (std::isalpha(static_cast<unsigned char>(c))){
                letters++;
            }
            else if (std::isdigit(static_cast<unsigned char>(c))){
                digits++;
            } 
            else if (std::isspace(static_cast<unsigned char>(c))) {
                spaces++;
            }
            else if (std::ispunct( static_cast<unsigned char>(c) )){
                punct++;
            }
        }


}

