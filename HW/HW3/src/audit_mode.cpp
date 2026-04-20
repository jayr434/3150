#include "audit_mode.h"
#include "validation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// return delim -- file extension based (default tab)
static char get_delimiter(std::string filename) {
    if (filename.size() >= 4 &&
        filename.substr(filename.size() - 4) == ".csv") {
        return ',';
    }
    return '\t';
}

void process_file(std::string input, std::string output) {
    std::ifstream in_file(input);
    if (!in_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::ofstream out_file(output, std::ios::app);
    if (!out_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        in_file.close();
        return;
    }

    char in_delim  = get_delimiter(input);
    char out_delim = get_delimiter(output);

    std::string line;
    while (std::getline(in_file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream s2(line);
        std::string username, email, password;

        std::getline(s2, username, in_delim);
        std::getline(s2, email,    in_delim);
        std::getline(s2, password);

        if (!is_valid_password(password)) {
            out_file << username << out_delim
                     << email    << out_delim
                     << password << "\n";
        }
    }

    in_file.close();
    out_file.close();
}

void menu() {
    int choice = 0;

    while (true) {
        std::cout << "1. Check a single password\n"
                  << "2. Process a TSV/CSV file\n"
                  << "3. Quit\n";

        std::cin >> choice;
        std::cin.ignore();   //newline

        if (choice == 1) {
            std::string password;
            std::cout << "Enter password: " << std::endl;
            std::getline(std::cin, password);
            std::cout << std::endl;

            if (is_valid_password(password)) {
                std::cout << "Valid" << std::endl;
            } else {
                std::cout << "Invalid" << std::endl;
            }

        } else if (choice == 2) {
            std::string input_path, output_path;

            std::cout << "Enter input file path: ";
            std::getline(std::cin, input_path);

            std::cout << "Enter output file path: ";
            std::getline(std::cin, output_path);

            process_file(input_path, output_path);

        } else if (choice == 3) {
            break;
        }
    }
}
