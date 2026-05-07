#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

int foo(const std::string &sentence)
{                                     // pass string by reference
    std::istringstream iss(sentence); // pretend the string is an input stream
    std::string word;
    int count = 0;

    while (iss >> word) // split by whitespace
    {
        // Check if the first character of the word is uppercase
        // char (from string) is signed, but the libraries we're using only deal with unsigned.
        // to cast for type-check safety
        if (!word.empty() && std::isupper(static_cast<unsigned char>(word[0])))
        {
            count++;
        }
    }
    return count;
}

int main()
{
    std::string userInput;

    std::cout << "Enter a sentence: ";
    std::getline(std::cin, userInput);

    int result = foo(userInput);

    std::cout << result << std::endl;

    return 0;
}