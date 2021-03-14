#include "engine/ui/append.hpp"
#include "engine/ui/list.hpp"
#include "engine/ui/pad_box.hpp"
#include "engine/ui/screen.hpp"
#include "engine/ui/text_box.hpp"
#include "engine/ui/vert_box.hpp"
#include <curses.h>
#include <iostream>
using namespace std;
using namespace Engine::UI;

// TODO: Handle keyboard, resize and other events
// discuss implementation details and draw a line between
// the engine and the game logic

int main() {
  Screen *screen = new Screen();
  PadBox *pbox = append<PadBox, map<enum PAD, uint16_t>>(
      screen, 1, 1,
      {{Engine::UI::PADDING_LEFT, 4},
       {Engine::UI::PADDING_RIGHT, 4},
       {Engine::UI::PADDING_TOP, 2},
       {Engine::UI::PADDING_BOTTOM, 2}});
  List *list = append<List, const wchar_t>(pbox, 1, 1, L'*');
  for (int i = 0; i < 21; i++) {
    VertBox *vbox = append<VertBox>(list, 1, 1);
    wstring str = L"Text on the left " + to_wstring(i);
    append<TextBox, const wchar_t *>(vbox, .7, 1, str.c_str());
    append<TextBox, const wchar_t *>(vbox, .3, 1, L"Text on the right");
  }

  if (screen->open()) {
    cout << "Error while opening screen" << endl;
    return 1;
  }

  int key;
  while ((key = getch()) != 'q') {
    if (key == KEY_RESIZE)
      screen->update();
  };

  screen->close();
  return 0;
}
