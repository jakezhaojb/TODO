#ifndef _PRIO_HPP
#define _PRIO_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool proc_info(string& task, int& prio, string info){
  int pos_p, pos_d;
  pos_p = info.find("--p");
  pos_d = info.find("--d");
  if (pos_p == string::npos && pos_d == string::npos) {
    task = info;
    prio = 1;
    return 0;
  } 
  else if (pos_p != string::npos){
    task = info.substr(0, pos_p-1);
    try{
      prio = std::stod(info.substr(pos_p+3));
    }
    catch(...){
      std::cout << "Input priority argument may not be a number." << std::endl;
      prio = 1;
      return 0;
    }
  }
  else { // (pos_d != string::npos)
    task = info.substr(pos_d+4);
    prio = 99;
  }
  return 1;
}


void trim(string & str){
  int n = str.find_first_not_of(" ");
  str.erase(str.begin(), str.begin()+n);
}



#endif
