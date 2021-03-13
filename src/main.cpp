#include "engine/ui/list.hpp"
#include "engine/ui/screen.hpp"
#include "engine/ui/text_box.hpp"
#include <curses.h>
#include <iostream>
using namespace std;

// TODO: Handle keyboard, resize and other events
// discuss implementation details and draw a line between
// the engine and the game logic

int main() {
  Engine::UI::Screen *screen = new Engine::UI::Screen();
  Engine::UI::List *list = Engine::UI::List::append(screen, 1, 1, L'*');
  Engine::UI::TextBox::append(
      list, 1, 1,
      L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
      L"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
      L"minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
      L"aliquip ex ea commodo consequat. Duis aute irure dolor in "
      L"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
      L"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
      L"culpa qui officia deserunt mollit anim id est laborum.");
  Engine::UI::TextBox::append(
      list, 1, 1,
      L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
      L"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
      L"minim veniam, quis nostrud exercitation ullamco laboris nisi ut ");
  Engine::UI::TextBox::append(list, 1, 1, L"Premere q per uscire");
  Engine::UI::TextBox::append(list, 1, 1, L"PS: il latino fa altamente cagare");

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
