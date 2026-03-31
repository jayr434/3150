#include <string>
#include <cctype>
#include <iostream>

int main(int argc, char * argv[]){
    char* s0 = argv[1];
	char* s1 = argv[2];     //c-style string input through argv[]
    char* s2 = argv[3];
	std::string stds0 = s0;     //convert
    std::string stds1 = s1;
    std::string stds2 = s2;
    std::cout << "s0 len: " << stds0.length() << "\n" << "s0 size: " << stds0.size() << std::endl;
    std::cout << "s1 len: " << stds1.length() << "\n" << "s1 size: " << stds1.size() << std::endl;
	std::cout << "s2 len: " << stds2.length() << "\ns2 size: " << stds2.size() << std::endl;
    

	return 0;
	
}
