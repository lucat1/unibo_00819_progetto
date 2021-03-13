#include "engine/ui/append.hpp"
#include "engine/ui/list.hpp"
#include "engine/ui/pad_box.hpp"
#include "engine/ui/screen.hpp"
#include "engine/ui/text_box.hpp"
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
  append<TextBox, const wchar_t *>(
      list, 1, 1,
      L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
      L"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
      L"minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
      L"aliquip ex ea commodo consequat. Duis aute irure dolor in "
      L"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
      L"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
      L"culpa qui officia deserunt mollit anim id est laborum.");
  PadBox *pbox1 = append<PadBox, map<enum PAD, uint16_t>>(
      list, 1, 1,
      {{Engine::UI::PADDING_LEFT, 4},
       {Engine::UI::PADDING_RIGHT, 4},
       {Engine::UI::PADDING_TOP, 2},
       {Engine::UI::PADDING_BOTTOM, 2}});
  append<TextBox, const wchar_t *>(
      pbox1, 1, 1,
      L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
      L"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
      L"minim veniam, quis nostrud exercitation ullamco laboris nisi ut ");
  append<TextBox, const wchar_t *>(list, 1, 1, L"Premere q per uscire");
  append<TextBox, const wchar_t *>(list, 1, 1,
                                   L"PS: il latino fa altamente cagare");

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
