#ifndef _COLOR_HPP
#define _COLOR_HPP


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SCREEN_WIDTH 141
#define DIALY_WIDTH 40
#define ONETIME_WIDTH 80
#define MID_WIDTH 20


void ColorPrint(std::string str, int level){
  //int color_code = rand() % 6 + 1;
  int color_code = level;
  switch(color_code){
    case 1:
      printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 2:
      printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 3:
      printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, str.c_str());
      break;
    case 4:
      printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 5:
      printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 6: // top priority
      printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, str.c_str());
      break;
    default:
      break;
  }
}

namespace std{

  void SetwColumnPrint(const string& a, const string&b, int color_code){
    bool Lflag, Rflag;
    string aL, aR, bL, bR;
    Lflag = a.size() > ONETIME_WIDTH ? true: false;
    Rflag = b.size() > DIALY_WIDTH ? true: false;
    if (Lflag) {
      aL = a.substr(0, ONETIME_WIDTH);
      aR = a.substr(ONETIME_WIDTH) + string(-a.size()+2*ONETIME_WIDTH, ' ');
    } else {
      aL = a;
      aR = string(ONETIME_WIDTH, ' ');
    }
    if (Rflag) {
      bL = b.substr(0, DIALY_WIDTH);
      bR = b.substr(DIALY_WIDTH);
    } else {
      bL = b;
      bR = " ";
    }
    // print out
    ColorPrint(aL, color_code);
    std::cout << string(MID_WIDTH, ' ') << bL;
    if (Lflag || Rflag){
      std::cout << std::endl;
      ColorPrint(aR, color_code);
      std::cout << string(MID_WIDTH, ' ') << bR;
    }
    std::cout << std::endl;
  }

  void DoubleColumnPrint(const string& ot, const string& dt){
    std::cout << setw(ONETIME_WIDTH) << left << ot
              << setw(5) << left << "☞"
              << setw(DIALY_WIDTH) << left << dt << endl;
  }

  void DoubleColumnPrint(const vector<string>& ot, const vector<string>& dt){
    if(ot.size() > dt.size()){
      for (int i = 0; i < dt.size(); i++)
        DoubleColumnPrint(ot[i], dt[i]);
      for (int i = dt.size(); i < ot.size(); i++)
        DoubleColumnPrint(ot[i], " ");
    } else{
      for (int i = 0; i < ot.size(); i++)
        DoubleColumnPrint(ot[i], dt[i]);
      for (int i = ot.size(); i < dt.size(); i++)
        DoubleColumnPrint(" ", dt[i]);
    }
}

}

#endif
