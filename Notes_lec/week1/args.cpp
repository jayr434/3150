#include <iostream>

int main(int argc, char* argv[]){
    std::cout << argv[0] << '\n' << "argument count " << argc << std::endl;

    for (int i = 0; i < argc; i++){
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }
    return 0;
}
