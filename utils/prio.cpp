#ifndef _PRIO_HPP
#define _PRIO_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool proc_info(string& task, int& proi, string info){
  int pos = info.find("-p");
  if (pos == string::npos) {
    task = info;
    proi = 1;
    return 0;
  } else{
    task = info.substr(0, pos-1);
    try{
      proi = std::stod(info.substr(pos+3));
    }
    catch(...){
      std::cout << "Input priority argument may not be a number." << std::endl;
      proi = 1;
    }
  }
}



#endif
