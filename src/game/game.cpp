/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Andreea Scrob #989372
  08/07/2021

  game.cpp: implementation of the main game logic.
*/

#include "game.hpp"
#include "../engine/audio.hpp"
#include "../engine/menu/main.hpp"
#include "../engine/menu/results.hpp"
#include "../engine/menu/select.hpp"
#include "../engine/menu/settings.hpp"
#include "../engine/scene/scene.hpp"
#include <iostream>
#include <signal.h>
#include <unistd.h>
using Engine::Audio;
using Engine::Drawable;
using Engine::Menu::Main;
using Engine::Menu::Results;
using Engine::Menu::Select;
using Engine::Menu::Settings;
using Engine::Scene::Scene;
using std::cout;

Game::Game::Game()
    : db("overengineered.conf.csv", "assets", "scoreboard.csv"),
      menu_manager(db, screen) {
  menu_manager.get_settings_manager().apply_settings();
  signal(SIGTERM, before_close);
}

void Game::Game::before_close(int) { Audio::stop(); }

int Game::Game::run() {
  if (!screen.open()) {
    cout << "Could not open screen. Perhaps your terminal is too small?\n";
    return 1;
  }

  screen.set_content<Main>();
  while (running) {
    running = loop();
  }
  screen.close();
  before_close(0); // useless parameter
  return 0;
}

bool Game::Game::loop() {
  // quit if usleep is blocked by an interrupt and the key is an ERR
  if (usleep(1000000 / menu_manager.get_settings_manager().get_fps()) == EINTR)
    return false;

  bool b;
  if (screen.get_content()->is_over()) {
    if ((b = menu_manager.change_content()) != running)
      return b;
  } else if (menu_manager.is_in_game())
    screen.send_event(Engine::Drawable::Event::redraw);

  handle_keypress();
  return true;
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
    if (!menu_manager.is_in_game())
      screen.send_event(Drawable::Event::move_up);
    else
      menu_manager.get_world().player.second.move_up();
    break;

  case 'j':
  case KEY_DOWN:
    if (!menu_manager.is_in_game())
      screen.send_event(Drawable::Event::move_down);
    else
      menu_manager.get_world().player.second.move_down();
    break;

  case 'h':
  case KEY_LEFT:
    if (!menu_manager.is_in_game())
      screen.send_event(Drawable::Event::move_left);
    else
      menu_manager.get_world().player.second.move_left();
    break;

  case 'l':
  case KEY_RIGHT:
    if (!menu_manager.is_in_game())
      screen.send_event(Drawable::Event::move_right);
    else
      menu_manager.get_world().player.second.move_right();
    break;
  case ERR:
    // ignore ncurses's getch errors
    break;
  };
}
