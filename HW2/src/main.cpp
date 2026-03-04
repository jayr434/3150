#include <iostream>
#include <string>
#include "text_mode.h"
#include "add_mode.h"
#include "stats_mode.h"

int main(int argc, char* argv[]){
  if (argc < 2){
    std::cout << "Usage: ./analyzer <mode> [arguments]" << std::endl;
    return 1;
  }
  
  std::string mode = argv[1];

  int cmode = 0;
  if (mode == "text" || mode =="Text") cmode = 1;
  else if (mode == "add" || mode == "Add") cmode = 2;
  else if (mode == "stats" || mode == "Stats") cmode = 3;

  switch(cmode){
    case 1:
      //text 
      text_mode::run(argc,argv);
      break;
    case 2:
      add_mode::run(argc,argv);
      break;
      //add 
    case 3:
      stats_mode::run(argc,argv);
      //stats 
    default:
      std::cout << "Invalid mode" << std::endl;
      return 1;
  }
}
