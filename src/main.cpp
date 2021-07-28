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
  /* Audio::fetch_tool(); */
  /* if (Audio::play("assets/sound/main_menu.wav")) { */
  /*   cout << "started playing" << endl; */
  /* } */
  /* int i = 0; */
  /* while (i < 5) { */
  /*   sleep(1); */
  /*   cout << "still running: " */
  /*        << (Audio::status() == Audio::PlayerState::playing ? "p" : "s") */
  /*        << endl; */
  /*   i++; */
  /* } */
  /* Audio::stop(); */
  Data::Database d("alma.conf.csv", "assets/",
                   "scoreboard.csv");
  World::World world(d);

  Screen screen;
  handle(screen.open());
  screen.set_content<Menu::Main>();

  int key;
  bool running = true, gaming = false;
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

        if (!screen.is_content<Menu::Select>()) {
          // go back to the main menu
          gaming = false;
          screen.set_content<Menu::Main>();
        } else {
          // otherwhise start a game
          // TODO: use this to provide the world a context of the current hero
          /* auto hero = screen.get_content<Menu::Select>()->get_result(); */
          gaming = true;
          screen.set_content<Scene::Scene, const World::World &>(world);
        }
      }
    } else if (gaming) {
      screen.send_event(Drawable::Event::redraw);
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
      if (!gaming)
        screen.send_event(Drawable::Event::move_up);
      else
        world.position->y = std::max(world.position->y - 1, 0);

      break;

    case 'j':
    case KEY_DOWN:
      if (!gaming)
        screen.send_event(Drawable::Event::move_down);
      else
        world.position->y = std::min(world.position->y + 1, 24);
      break;

    case 'h':
    case KEY_LEFT:
      if (!gaming)
        screen.send_event(Drawable::Event::move_left);
      else
        world.position->dec_x();
      break;

    case 'l':
    case KEY_RIGHT:
      if (!gaming)
        screen.send_event(Drawable::Event::move_right);
      else
        world.position->inc_x();
      break;
    case ERR:
      // ignore ncurses's getch errors
      break;
    };
  }
  return 0;
}
