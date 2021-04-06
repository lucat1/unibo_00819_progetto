#include "engine/menu/main.hpp"
#include "engine/menu/settings.hpp"
#include "engine/screen.hpp"
#include <iostream>
#include <unistd.h>
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
  handle(screen.open());
  screen.set_content<Menu::Main>();
  Nostd::Vector<Data::Setting> settings;

  int key = -1, running = true;
  while (running) {
    // quit if usleep returns an error
    if (usleep(1000000 / 25)) // 25fps
      break;

    if (screen.get_content()->is_over()) {
      if (screen.is_content<Menu::Main>()) {
        // do something when the main menu is exited
        auto res = screen.get_content<Menu::Main>()->get_result();
        switch (res) {
        case Menu::Main::Result::quit:
          running = false;
        case Menu::Main::Result::settings:
          screen.set_content<Menu::Settings, Nostd::Vector<Data::Setting>>(
              settings);
        default:
          break;
        }
      } else if (screen.is_content<Menu::Settings>()) {
        // do something when the settings menu is closed
        screen.set_content<Menu::Main>();
      }
    }

    // keyboard handling
    key = getch();
    if (key != ERR) {
      switch (key) {
      case KEY_RESIZE:
        handle(screen.reposition());
        break;

      case '\n':
      case KEY_ENTER: // enter key for the numpad
        screen.send_event(Drawable::Event::interact);
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
  }

  return 0;
}
