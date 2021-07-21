#include "engine/menu/main.hpp"
#include "data/database.hpp"
#include "engine/colorable.hpp"
#include "engine/menu/select.hpp"
#include "engine/menu/settings.hpp"
#include "engine/scene/scene.hpp"
#include "engine/screen.hpp"
#include "world/world.hpp"
#include <fstream>
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
  Data::Database d("tests/alma.conf.csv", "tests/assets/",
                   "tests/scoreboard.csv");
  World::World world(d);

  Screen screen;
  handle(screen.open());
  screen.set_content<Menu::Main>();

  int key;
  bool running = true;
  while (running) {
    // quit if usleep is blocked by an interrupt and the key is an ERR
    if (usleep(1000000 / 25) == EINTR) // 25fps
      running = false;

    if (screen.get_content()->is_over()) {
      if (screen.is_content<Menu::Main>()) {
        // do something when the main menu is exited
        auto res = screen.get_content<Menu::Main>()->get_result();
        switch (res) {
        case Menu::Main::Result::quit:
          running = false;
          break;
        case Menu::Main::Result::settings:
          screen.set_content<Menu::Settings,
                             const Nostd::Vector<Data::Setting> &>(
              d.settings());
          break;
        case Menu::Main::Result::play:
          // TODO: change me
          /*screen.set_content<Menu::Results,
                             const Nostd::List<Data::Pawns::Result>
             &>(d.results());
                             */
          screen.set_content<Menu::Select,
                             const Nostd::Vector<Data::Pawns::Hero> &>(
              d.heroes());
          break;
        default:
          break;
        }
      } else {
        // save settings if that was the previous menu
        if (screen.is_content<Menu::Settings>())
          d.settings() = screen.get_content<Menu::Settings>()->get_result();

        if (!screen.is_content<Menu::Select>())
          // go back to the main menu
          screen.set_content<Menu::Main>();
        else {
          // otherwhise start a game
          // TODO: use this to provide the world a context of the current hero
          /* auto hero = screen.get_content<Menu::Select>()->get_result(); */
          screen.set_content<Scene::Scene, const World::World &>(world);
        }
      }
    }

    // keyboard handling
    key = getch();
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

    case 'h':
    case KEY_LEFT:
      screen.send_event(Drawable::Event::move_left);
      break;

    case 'l':
    case KEY_RIGHT:
      screen.send_event(Drawable::Event::move_right);
      break;
    case ERR:
      // ignore ncurses's getch errors
      break;
    };
  }
  return 0;
}
