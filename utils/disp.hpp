#ifndef _COLOR_HPP
#define _COLOR_HPP


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
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
#define DIALY_WIDTH 50
#define ONETIME_WIDTH 80
#define MID_WIDTH 10


void ColorPrint(std::string str, int level){
  int color_code = level;
  switch(color_code){
    case 1:
      printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 2:
      printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 3:
      printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 4:
      printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET, str.c_str()) ;
      break;
    case 5: // top priority
      printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, str.c_str());
      break;
    case 99:
      printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, str.c_str());
      break;
    default:
      std::cout << str;
      break;
  }
}

namespace std{

  void SetwColumnPrint(const string& a, const string& b, int color_code){
    bool Lflag, Rflag;
    string aL, aR, bL, bR;
    Lflag = a.size() > ONETIME_WIDTH ? true: false;
    Rflag = b.size() > DIALY_WIDTH ? true: false;
    if (Lflag) {
      aL = a.substr(0, ONETIME_WIDTH);
      aR = a.substr(ONETIME_WIDTH) + string(-a.size()+2*ONETIME_WIDTH, ' ');
    } else {
      aL = a + string(ONETIME_WIDTH-a.size(), ' ');
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
    std::cout << string(MID_WIDTH-1, ' ') << "▓★   ";
    ColorPrint(bL, 99);
    if (Lflag || Rflag){
      std::cout << std::endl;
      ColorPrint(aR, color_code);
      std::cout << string(MID_WIDTH-1, ' ') << "▓★   ";
      ColorPrint(bR, 99);
    }
    std::cout << std::endl;
  }

  void DoubleColumnPrint(const vector<string>& ot, const vector<string>& dt, vector<int> color_codes){
    assert(color_codes.size() == ot.size());
    // decoration
    string dec_top, dec_bottom;
    for (int i = 0; i < SCREEN_WIDTH; i++) {
      dec_top.append("✪");
      dec_bottom.append("✪");
    }
    std::cout << dec_top << std::endl;
    if(ot.size() > dt.size()){
      for (int i = 0; i < dt.size(); i++)
        SetwColumnPrint(ot[i], dt[i], color_codes[i]);
      for (int i = dt.size(); i < ot.size(); i++)
        SetwColumnPrint(ot[i], " ", color_codes[i]);
    } else{
      for (int i = 0; i < ot.size(); i++)
        SetwColumnPrint(ot[i], dt[i], color_codes[i]);
      for (int i = ot.size(); i < dt.size(); i++)
        SetwColumnPrint(" ", dt[i], 1);
    }
    std::cout << dec_bottom << std::endl;
}

}

#endif
