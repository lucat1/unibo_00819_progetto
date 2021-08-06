#include "game.hpp"
#include "../engine/menu/main.hpp"
#include "../engine/menu/select.hpp"
#include "../engine/menu/settings.hpp"
#include "../engine/scene/scene.hpp"
#include <iostream>
#include <unistd.h>
using Engine::Drawable;
using Engine::Menu::Main;
using Engine::Menu::Select;
using Engine::Menu::Settings;
using Engine::Scene::Scene;
using std::cout;

Game::Game::Game()
    : db("overengineered.conf.csv", "assets/", "scoreboard.csv"), world(db) {}

int Game::Game::run() {
  if (!screen.open()) {
    cout << "Could not open screen. Perhaps your terminal is too small?\n";
    return 1;
  };
  screen.set_content<Main>();
  while (running) {
    running = loop();
  }

  screen.close();
  return 0;
}

bool Game::Game::loop() {
  // quit if usleep is blocked by an interrupt and the key is an ERR
  if (usleep(1000000 / 25) == EINTR) // 25fps
    return false;

  if (screen.get_content()->is_over())
    change_content();
  else if (in_game)
    screen.send_event(Engine::Drawable::Event::redraw);

  handle_keypress();
  return true;
}

void Game::Game::change_content() {
  if (screen.is_content<Main>()) {
    // do something when the main menu is exited
    auto res = screen.get_content<Main>()->get_result();
    switch (res) {
    case Main::Result::quit:
      running = false;
      break;
    case Main::Result::settings:
      screen.set_content<Settings, const Nostd::Vector<Data::Setting> &>(
          db.settings());
      break;
    case Main::Result::play:
      // TODO: change me
      /*screen.set_content<Menu::Results,
                         const Nostd::List<Data::Pawns::Result>
         &>(d.results());
                         */
      screen.set_content<Select, const Nostd::Vector<Data::Pawns::Hero> &>(
          db.heroes());
      break;
    default:
      break;
    }
  } else {
    // save settings if that was the previous menu
    if (screen.is_content<Settings>())
      db.settings() = screen.get_content<Settings>()->get_result();
    // TODO: write settings
    if (!screen.is_content<Select>()) {
      // go back to the main menu
      in_game = false;
      screen.set_content<Main>();
    } else {
      // otherwhise start a game
      // TODO: use this to provide the world a context of the current hero
      /* auto hero = screen.get_content<Menu::Select>()->get_result(); */
      in_game = true;
      screen.set_content<Scene, const World::World &>(world);
    }
  }
}

void Game::Game::handle_keypress() {
  int key = getch();
  switch (key) {
  case KEY_RESIZE:
    if (!screen.reposition())
      running = false;
    break;

  case '\n':
  case KEY_ENTER: // enter key for the numpad
    screen.send_event(Drawable::Event::interact);
    break;

  case 'k':
  case KEY_UP:
    if (!in_game)
      screen.send_event(Drawable::Event::move_up);
    else
      world.position->y = std::max(world.position->y - 1, 0);

    break;

  case 'j':
  case KEY_DOWN:
    if (!in_game)
      screen.send_event(Drawable::Event::move_down);
    else
      world.position->y = std::min(world.position->y + 1, 24);
    break;

  case 'h':
  case KEY_LEFT:
    if (!in_game)
      screen.send_event(Drawable::Event::move_left);
    else
      world.position->dec_x();
    break;

  case 'l':
  case KEY_RIGHT:
    if (!in_game)
      screen.send_event(Drawable::Event::move_right);
    else
      world.position->inc_x();
    break;
  case ERR:
    // ignore ncurses's getch errors
    break;
  };
}
