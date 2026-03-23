#include "../include/audit_mode.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc == 3) {
        std::string input(argv[1]);
        std::string output(argv[2]);
        process_file(input, output);
        return 0;
    }

    menu();
    return 0;
}
