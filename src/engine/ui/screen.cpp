#include "screen.hpp"
#include <iostream>
#include <ncurses.h>
using namespace std;

// screen wraps the whole ncurses screen in a box of SCREEN_WIDTHxSCREEN_HEIGHT
// that is centered on the screen and repositioned properly on resizes
//
// Furthermore the screen class keeps track of the terminal dimentions
// to center boxes as we see fit and also calls helper functions like
// `raw`, `keypad` and `noecho` to properly get the user input.

Engine::UI::Screen::Screen() : Box(SCREEN_COLS, SCREEN_LINES) {}

bool Engine::UI::Screen::can_fit() {
  getmaxyx(window, terminal_lines, terminal_cols);

  // check that the terminal is big enough to fit the game
  if (terminal_cols < SCREEN_COLS || terminal_lines < SCREEN_LINES)
    return true;

  x = (terminal_cols - SCREEN_COLS) / 2;
  y = (terminal_lines - SCREEN_LINES) / 2;

  return false;
}

bool Engine::UI::Screen::open() {
  window = initscr(); // terminal should be equal to stdscr
  if (window == NULL)
    return true;

  clear();   // clear the screen and
  refresh(); // send the changes to the user so we can start drawing

  noecho(); // prevents user-inputted charters to be displayed on the screen
  raw();    // with raw we intercept all keystrokes and prevent ^C from quitting
            // the game
  curs_set(0); // hide the cursor by default
  keypad(
      window,
      false); // the second argument is set to `false` to caputre RESIZE events

  if (can_fit())
    return true;

  window = newwin(SCREEN_LINES + 2, SCREEN_COLS + 2, y, x);
  box(window, ACS_VLINE, ACS_HLINE);
  show(window, 1, 1);
  wrefresh(window);
  return false;
}

bool Engine::UI::Screen::update() {
  if (can_fit())
    return true;

  // clear the previous screen
  clear();
  refresh();

  mvwin(window, x, y);
  wrefresh(window);

  return false;
}

void Engine::UI::Screen::close() { endwin(); }
