#include "screen.hpp"
#include <iostream>
#include <ncurses.h>
using namespace std;
using namespace Engine;

// screen wraps the whole ncurses screen in a box
// of SCREEN_WIDTHxSCREEN_HEIGHT that is centered on the
// screen and repositioned properly on resizes
//
// Furthermore the screen class keeps track of the terminal dimentions
// to center boxes as we see fit. We do also call helper functions like
// `raw` and `keypad` to properly get all the keystrokes the user presses.

bool Screen::measure() {
  getmaxyx(terminal, terminal_lines, terminal_cols);

  // check that the terminal is big enaugh to fit the game
  if (terminal_cols < SCREEN_COLS || terminal_lines < SCREEN_LINES)
    return true;

  terminal_offset_cols = (terminal_cols - SCREEN_COLS) / 2;
  terminal_offset_lines = (terminal_lines - SCREEN_LINES) / 2;

  return false;
}

// TODO: Handle keyboard, resize and other events
// discuss implementation details and draw a line between
// the engine and the game logic

bool Screen::open() {
  terminal = initscr(); // terminal should be equal to stdscr
  if (terminal == NULL)
    return true;

  clear();   // clear the screen and
  refresh(); // send the changes to the user so we can start drawing

  noecho(); // prevents user-inputted charters to be displayed on the screen
  raw();    // with raw we intercept all keystrokes and prevent ^C from quitting
            // the game
  keypad(terminal, true); // TODO: document second argument from man pages

  if (measure())
    return true;

  window = newwin(SCREEN_LINES, SCREEN_COLS, terminal_offset_lines,
                  terminal_offset_cols);
  box(window, '+', '-');
  wrefresh(window);
  return false;
}

void Screen::close() { endwin(); }
