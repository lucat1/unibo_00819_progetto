#include "draw.hpp"
#include <iostream>
#include <ncurses.h>

int main() {
  init();
  std::string str = "I am centered";
  centerw(str.c_str());
  refresh();
  getchar();
  quit();

  return 0;
}
