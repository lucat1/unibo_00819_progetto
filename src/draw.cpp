#include "draw.hpp"
#include <ncurses.h>
#include <string>

void init() {
  initscr();
  refresh();
}

void quit() { endwin(); }

void centerw(const char *str) {
  int cols, rows;
  getmaxyx(stdscr, rows, cols);

  int col = (cols / 2) - strlen(str) / 2;
  mvprintw(rows / 2, col, "%s", str);
}
