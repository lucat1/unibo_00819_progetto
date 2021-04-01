#include "engine/menu/main.hpp"
#include "engine/screen.hpp"
#include <iostream>
using namespace std;
using namespace Engine;

void handle(bool can_display) {
  if (can_display)
    return;

  cout << "Error while opening screen" << endl;
  exit(1);
}

int main() {
  Screen screen;
  screen.open();
  handle(screen.open());

  Menu::Main *main_menu = new Menu::Main(screen.get_container());
  screen.set_content(main_menu);

  int key;
  while ((key = getch()) != 'q') {
    switch (key) {
    case KEY_RESIZE:
      handle(screen.reposition());
      break;
    case 'k':
    case KEY_UP:
      screen.send_event(Drawable::Event::move_up);
      break;
    case 'j':
    case KEY_DOWN:
      screen.send_event(Drawable::Event::move_down);
      break;
    };
  }

  return 0;
}
