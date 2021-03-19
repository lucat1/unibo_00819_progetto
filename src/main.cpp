#include "engine/ui/append.hpp"
#include "engine/ui/list.hpp"
#include "engine/ui/screen.hpp"
#include "engine/ui/text_box.hpp"
#include <curses.h>
#include <iostream>
using namespace std;
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
  Box *pbox = append<Box>(screen, 1, 1,
                          {{Box::PADDING_LEFT, 4},
                           {Box::PADDING_RIGHT, 4},
                           {Box::PADDING_TOP, 2},
                           {Box::PADDING_BOTTOM, 2}});
  List *list = append<List, const wchar_t>(pbox, 1, 1);
  for (int i = 0; i < 21; i++) {
    Box *line = append<Box>(list, 1, 1, {{Box::Props::DIRECTION, 1}});
    wstring str = L"Text on the left " + to_wstring(i);
    append<TextBox, const wchar_t *>(line, .5, 1, {}, str.c_str());
    append<TextBox, const wchar_t *>(line, .5, 1, {{Box::Props::FLOAT, 1}},
                                     L"Text on the right");
  }

  handle(screen, screen->open());

  int key;
  while ((key = getch()) != 'q') {
    if (key == KEY_RESIZE) {
      handle(screen, screen->update());
    }
  };

  screen->close();
  return 0;
}
