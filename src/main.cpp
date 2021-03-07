#include "engine/ui/screen.hpp"
#include <curses.h>
#include <iostream>
using namespace std;

// TODO: Handle keyboard, resize and other events
// discuss implementation details and draw a line between
// the engine and the game logic

int main() {
  Engine::Screen screen;

  if (screen.open()) {
    cout << "Error while opening screen" << endl;
    return 1;
  }

  int key;
  while ((key = getch()) != 'q') {
    if (key == KEY_RESIZE)
      screen.recenter();
  };

  screen.close();
  return 0;
}
