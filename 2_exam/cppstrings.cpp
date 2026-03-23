#include <string>
#include <cctype>
#include <iostream>

int main(int argc, char * argv[]){
	char* s = argv[2];   //c-style string, char array w/ null terminator
	//convert to cpp string: std::string
	std::string s2 = "*string*";
	std::cout << s2.length() << std::endl;
	std::cout << s2.size() << std::endl;
    std::cout << "c string " << s << std::endl;


	return 0;
	
}
