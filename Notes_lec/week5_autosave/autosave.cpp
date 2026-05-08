#include <iostream>
#include <fstream>
#include "autosave.h"
using std::cout, std::cin, std::endl;

namespace autosave_tools {
    void autosave(){
        std::string line;
        std::string SourceName;
        std::string DestName;
        cout<<"Enter File to copy from:  " << endl;
        std::getline(cin, SourceName);

        std::ifstream source(SourceName);

        if (!source){
            std::cerr <<"Could not find the file to read from\n"<<endl;
            return;
        }
        std::cout<<"Enter the new name of the file to create and copy to : " <<endl;
        std::getline (cin,DestName);

        std::ofstream dest(DestName);

        if(!dest){
            std::cerr<<"Could not create the file." <<endl;
            return;
        }


        while(std::getline(source, line)){
            dest << line<< '\n';
        }
        cout<<"File copied sucessfully.\n"<<endl;


   }
}
