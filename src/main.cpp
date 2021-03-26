#include "engine/screen.hpp"
#include "engine/ui/append.hpp"
#include "engine/ui/list.hpp"
#include "engine/ui/text_box.hpp"
#include <curses.h>
#include <iostream>
using namespace std;
using namespace Engine;
using namespace Engine::UI;

// TODO: Handle keyboard, resize and other events
// discuss implementation details and draw a line between
// the engine and the game logic

void handle(Screen *screen, bool can_display) {
  if (can_display)
    return;

  screen->close();
  cout << "Error while opening screen" << endl;
  exit(1);
}

int main() {
  Screen *screen = new Screen();
  handle(screen, screen->open());

  int key;
  while ((key = getch()) != 'q') {
    switch (key) {
    case KEY_RESIZE:
      screen->reposition();
      break;
    };
  }

  delete screen;
  return 0;
}
