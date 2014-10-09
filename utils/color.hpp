#ifndef _COLOR_HPP
#define _COLOR_HPP


#include <cstdio>
#include <cstdlib>
#include <string>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


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

#endif
